#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "determination_temperature_pH.h"



#define M_PI 3.14159265358979323846     // definition of PI approched because my VS-code don't reconise M_PI from <math.h>

// Maximum density of all the species [kg.m^-2]

#define MAX_DENSITE_W 35.0
#define MAX_DENSITE_A 15.0
#define MAX_DENSITE_C 50.0
#define MAX_DENSITE_S 18.0

#define FACTEUR_REDUCTION 0.95 // If species reach these maximum densities, they are reduced by this factor 



// Global parameters of the model, see report for the units

double PHI1 = 0.1, PHI2 = 0.05, PHI3 = 0.03, PHI4 = 0.02 ;
double THETA1 = 0.5, THETA2 = 0.4 ;
double MU = 0.02, DELTA1 = 0.01, DELTA2 = 0.005 ;
double U = 0.001, p = 0.1, q = 0.15 ;

// Function to save results in a CSV file specially deesign for the parameters of the differential system of equations

void save_to_csv(const char *filename, double *t, double *w, double *a, double *c, double *s, double *T, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier") ;
        return ;
    }
    fprintf(file, "Time,W,A,C,S,Temperature\n") ;
    for (int i = 0 ; i < size ; i++) {
        fprintf(file, "%f,%f,%f,%f,%f,%f\n", t[i], w[i], a[i], c[i], s[i], T[i]) ;
    }
    fclose(file) ;
}

// Function for simulate the ecosystem with the impact of temperature, using Euler's methods

void simulate_ecosystem(double max_time, double dt, double *mean_coeff, double *percent_init_pop, double *densite_pop, double facteur_climatique) {

    int steps = (int)(max_time / dt) ;  // You will see in the main code of C, but steps correspond to 7300 days (equal to 20 years) and we will iterate day per day

    // Creation of malloc for time, each species and temperature

    double *time = malloc(steps * sizeof(double)) ;
    double *w = malloc(steps * sizeof(double)) ;    //wrasses
    double *a = malloc(steps * sizeof(double)) ;    //anemones
    double *c = malloc(steps * sizeof(double)) ;    //corals
    double *s = malloc(steps * sizeof(double)) ;    //starfishs
    double *T = malloc(steps * sizeof(double)) ;    //temperature

    // Check if any of the memory allocations failed

    if (!time || !w || !a || !c || !s || !T) { 
        printf("Erreur : allocation mémoire échouée.\n") ; // Print an error message indicating memory allocation failure
        return ; // Exit the function early to avoid using null pointers
    }


    double surface = 3e6 * 1.2 ;                                 // Corrected projected surface area of the marina park
    double initial_surface[4], biomasses[4], densite[4] ;        // Variables to adjust the units for the surface of the marina park

    // Adjusting the units population for the surface of the marina park

    for (int i = 0; i < 4; i++) {
        initial_surface[i] = surface * percent_init_pop[i] ;    
        biomasses[i] = initial_surface[i] * densite_pop[i] ;
        densite[i] = biomasses[i] / surface ;                    // Initial densite [kg.m^-2] of the species
    }

    // Itarations to solve the differential system equations, with one step correspond to one day

    for (int i = 0; i < steps; i++) {

        time[i] = i * dt ;
        w[i] = densite[0] ;
        a[i] = densite[1] ;
        c[i] = densite[2] ;
        s[i] = densite[3] ;
        T[i] = temperature(time[i], mean_coeff[0], mean_coeff[1], facteur_climatique) ;
        T[i] = fmin(fmax(T[i], 25), 35) ;                                                   // Limitation of température, realistic for the temperature of sea at Gilis islands


        // Updating the impact of temperature

        double gamma_w = facteur_temperature_w(time[i], mean_coeff[0], mean_coeff[1], facteur_climatique) ;
        double gamma_a = facteur_temperature_a(time[i], mean_coeff[0], mean_coeff[1], facteur_climatique) ;
        double gamma_c = facteur_temperature_acropora(time[i], mean_coeff[0], mean_coeff[1], facteur_climatique) ;
        double gamma_s = facteur_temperature_s(time[i], mean_coeff[0], mean_coeff[1], facteur_climatique) ;

        
        // Gamma limitation at 1.0

        gamma_w = fmin(gamma_w, 1.0) ;
        gamma_a = fmin(gamma_a, 1.0) ;
        gamma_c = fmin(gamma_c, 1.0) ;
        gamma_s = fmin(gamma_s, 1.0) ;

        // differential system equations applied for the Euler's method

        double dw = densite[0] * (PHI1 * (1 - (densite[0] / (1 + THETA1 * densite[2]))) + DELTA1 * densite[3]) - MU * densite[0] * densite[1] - gamma_w * T[i] ;
        double da = densite[1] * (PHI2 * (1 - (densite[1] / (1 + THETA2 * densite[2]))) - MU * densite[0] * densite[1]) - gamma_a * T[i] ;
        double dc = densite[2] * (PHI3 * (1 - densite[2]) - (U * densite[3]) / (densite[2] + p)) - gamma_c * T[i] ;
        double ds = densite[3] * (PHI4 * (1 - densite[3]) - DELTA2 * densite[0] - (densite[2] / (densite[2] + q))) - gamma_s * T[i] ;

        densite[0] += dw * dt;
        densite[1] += da * dt;
        densite[2] += dc * dt;
        densite[3] += ds * dt;

        // Checking thresholds, we using the facor of reduction define at the top of this code

        if (densite[0] > MAX_DENSITE_W) densite[0] *= FACTEUR_REDUCTION ;
        if (densite[1] > MAX_DENSITE_A) densite[1] *= FACTEUR_REDUCTION ;
        if (densite[2] > MAX_DENSITE_C) densite[2] *= FACTEUR_REDUCTION ;
        if (densite[3] > MAX_DENSITE_S) densite[3] *= FACTEUR_REDUCTION ;

        // Extinction if negative density

        for (int j = 0; j < 4; j++) {
            if (densite[j] < 0) densite[j] = 0 ;
        }
    }

    // Save the simulation results to a CSV file for further analysis or visualization
    
    save_to_csv("Internal/ecosystem_simulation_results.csv", time, w, a, c, s, T, steps);

    // Free the dynamically allocated memory for each array to prevent memory leaks
    free(time) ; // Free memory allocated for the time array
    free(w) ;    // Free memory allocated for the water quality array
    free(a) ;    // Free memory allocated for the acidity array
    free(c) ;    // Free memory allocated for the coral health array
    free(s) ;    // Free memory allocated for the salinity array
    free(T) ;    // Free memory allocated for the temperature array


    printf("Simulation terminée. Résultats sauvegardés dans 'ecosystem_simulation_results.csv'.\n");
}


