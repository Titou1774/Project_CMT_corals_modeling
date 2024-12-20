#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// We call all this modules to use their functions

#include "functions_humanimpact.c"
#include "determination_temperature_pH.c"
#include "implementation_equa_diff.c"


// Time steps and limits

#define DT 0.01 	// equivalent to one day
#define MAX_TIME 73 // equivalent to 20 years

#define facteur_climatique 0.15 // See report for this choice of parameter
#define nbr_month 12



// ------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------ PARAMETERS----------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------
//This part of code contains all the parameters that you can change as you want for the simulation. We advice you to take the following, to have a realistic simulation.


#define taillex 100     // dimensions of water field
#define tailley 100
#define depart_x 0   			// Its the departure of simulation, we can think about a port that release C02 with boat, or just a factory that eject gas
#define depart_y 0
#define concentration_c02 275  		// We know that the concentration in the atmosphere is about 300 ppm. We assume that a single boat release a bit less than this
#define r 3					//We assume an initial plume radius of 3 meters
#define years 20				//Simulation over 20 years




int main() {


    // ------------------------------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------ Temperature Impact ----------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------------------------------


	// This temperature come from somes data set that come from differents sources (cf reports for this sources). They are hardcoded values, rather than being read in as it would 
    // not be worthwhile to add text and csv files for them.

    double releve_temperatures1[] = {28.7, 28.8, 29.2, 29.7, 29.6, 28.8, 28.2, 27.8, 28.0, 28.7, 29.4, 29.3} ; 			// Temperature record for the Gilis Islands #1
    double releve_temperatures2[] = {29.3, 29, 29.5, 29.4, 29.3, 28.5, 27.5, 27.2, 27.8, 28.8, 29.5, 29.9} ; 			// Temperature record for the Gilis Islands #2
    double releve_temperatures3[] = {29, 29, 29, 29, 29, 28, 28, 27, 27, 28, 29, 29} ; 									// Temperature record for the Gilis Islands #3
    double releve_temperatures4[] = {29.3, 28.8, 29.3 , 29.4, 29.1, 28.5 , 27.7 , 27.4 , 27.6 , 28.8 , 29.7 , 29.7} ;   // Temperature record for the Gilis Islands #4
    double Time[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // Time (month)

    double coeff1[2], coeff2[2], coeff3[2], coeff4[2] ;

	// We use #include "determination_temperature_pH.c" to find the coefficiant of linear regression for each temperature record

    calcule_regression_lineaire(releve_temperatures1,Time, nbr_month, coeff1) ;
    calcule_regression_lineaire(releve_temperatures2,Time, nbr_month, coeff2) ;
    calcule_regression_lineaire(releve_temperatures3,Time, nbr_month, coeff3) ;
    calcule_regression_lineaire(releve_temperatures4,Time,nbr_month, coeff4) ;

    static double mean_coefficients[2] ; 

    for ( int i = 0 ; i<2 ; i++) {
        mean_coefficients[i]= (coeff1[i] + coeff2[i] + coeff3[i] + coeff4[i]) / 4 ;  // We take the mean value of this coefficiants to be more precise
        printf("%f ", mean_coefficients[i]) ;
    }


    double percent_initial_population[] = {0.17, 0.03 , 0.35 , 0.01} ; 	// Percentages occupied by each population at initial conditions
    
    double densite_population[] = {0.01 , 0.02 , 7.0, 0.15} ;  			// Typical biomass densities in [kg/m^2]
    
	// Now we use the #include "implementation_equa_diff.c" to solve the differential system equations

    simulate_ecosystem(MAX_TIME, DT, mean_coefficients, percent_initial_population, densite_population, facteur_climatique) ;





    // --------------------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------ Antropogenic Impact -----------------------------------------------------------------
    // --------------------------------------------------------------------------------------------------------------------------------

   

    srand(time(NULL)); 									// We initialise a random number with this command
    FILE* output2 = fopen("Internal/C02_terrain.csv", "w");    	 // File to collect the concentration of C02 in the air
    FILE* output3 = fopen("Internal/acidite_terrain.csv", "w");   // File to collect the pH of water
    

	// Verification that the file is opening, and that there is no mistakes in file path
    if (output2 == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier de sortie.\n");
        return 1;
    }
    if (output3 == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier de sortie.\n");
        return 1;
    }
	
	
	// Initializing of data, we create 3 1D arrays, first for the C02 concentration in the atmosphere,
	//the second for the pH of water, the last one for the mass per squared meter of corals, ie the health
	//We use dynamic memroy allocation (malloc) to change the dimensions of water field if we want to see the impact on a bigger land

    double* pollution = malloc(taillex * tailley * sizeof(double));
    double* acidite = malloc(taillex * tailley * sizeof(double));
    double* sante = malloc(taillex * tailley * sizeof(double));
    
	// We make loops to initialize all the arrays
    for(int i = 0; i<taillex; i++){
		for(int j = 0; j<tailley; j++){
			acidite[j*taillex+i] = 8.1;       // We are initializing the pH of water field
		}
	} 
	      
    for (int i = 0; i < taillex; i++) {
        for (int j = 0; j < tailley; j++) {
            pollution[j * taillex + i] = 300;    // We talk of ppm concentration, according to data collected 
        }
    }
    
    for(int i = 0; i<taillex; i++){
		for(int j = 0; j<tailley; j++){
			sante[j*taillex+i] = 7;           // We are initializing the health of corals, in kg.m⁻2
		}
	} 
    
	for(int i = 0; i<years; i++){
		for(int day = 0; day<365; day++){
			
			simulePollution(depart_x,depart_y,r,concentration_c02, pollution);
			absorption(pollution, taillex,tailley, 0.3, 1);
			
		}
		for(int x = 0; x<taillex; x++){
			for(int y = 0; y<tailley; y++){
				if(pollution[y*taillex+x]>350){
					acidite[y*taillex+x] -= 0.005;        // We assume here that only 30% of C02 concentration is absorbated by the water
				}
				else if(pollution[y*taillex+x]>400){
					acidite[y*taillex+x] -= 0.01;		// The values are estimation, due to lack of data
				}
				else if(pollution[y*taillex+x]>450){
					acidite[y*taillex+x] -= 0.02;
				}
				else if(pollution[y*taillex+x]>500){
					acidite[y*taillex+x] -= 0.04;
				}
				else if(pollution[y*taillex+x]>550){
					acidite[y*taillex+x] -= 0.06;
				}
				else if(pollution[y*taillex+x]>600){
					acidite[y*taillex+x] -= 0.08;
				}
				else if(pollution[y*taillex+x]>650){
					acidite[y*taillex+x] -= 0.1;
				}
				else if(pollution[y*taillex+x]>700){
					acidite[y*taillex+x] -= 0.2;
				}
				else if(pollution[y*taillex+x]>750){
					acidite[y*taillex+x] -= 0.4;
				}

				}

			}
		}

	
	
	// Loop to simulate the coral health with a change in pH
	for(int x = 0; x<taillex; x++){
			for(int y = 0; y<tailley; y++){
				if((acidite[y*taillex+x]<=8.1) && (acidite[y*taillex+x]>8.08)){
					sante[y*taillex+x] -= (randomNumber(4)+2)/10;  // The number here are an estimation, we tried to be realistic as possible
				}
				else if((acidite[y*taillex+x]<=8.08) && (acidite[y*taillex+x]>8.06)){
					sante[y*taillex+x] -= (randomNumber(4)+6)/10;
				}
				
				else if((acidite[y*taillex+x]<=8.06) && (acidite[y*taillex+x]>8.04)){
					sante[y*taillex+x] -= (randomNumber(4)+8)/10 ;
				}
				else if((acidite[y*taillex+x]<=8.04) && (acidite[y*taillex+x]>8.02)){
					sante[y*taillex+x] -= (randomNumber(4)+10)/10;
				}
				else if((acidite[y*taillex+x]<=8.02) && (acidite[y*taillex+x]>=7.99)){
					sante[y*taillex+x] -= (randomNumber(4)+12)/10;
				}

			}
		}
	//Loop to print the values in csv files, used to plot png figures and collect the values
	for(int i = 0; i<taillex; i++){
		for(int j = 0; j<tailley; j++){
			fprintf(output2,"%f\n", pollution[j*taillex+i]);
			fprintf(output3,"%f\n", acidite[j*taillex+i]);
		}
	}
	// Part to collect data to create a dataset for the linear regression
	
	 
    double valeursUniquesPH[taillex * tailley];                         // Arrays to stock unique values of coral pH 
    double santeAssociee[taillex * tailley];							// Arrays to stock unique values of coral health

    int nombreValeursUniques = collecterValeursUniquesEtSante(
        acidite, sante, taillex * tailley, valeursUniquesPH, santeAssociee);

    
    FILE* outputUniques = fopen("Internal/valeurs_uniques_pH_sante.csv", "w");   // Save unique values of health and pH on a csv file
    if (outputUniques == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier des valeurs uniques.\n");
        return 1;
    }

	//Loop to print the values for linear regression, the model
    for (int i = 0; i < nombreValeursUniques; i++) {
        fprintf(outputUniques, "%f, %f\n", valeursUniquesPH[i], santeAssociee[i]);
    }

    //Verify if the simulation is correctly done
    printf("Valeurs uniques de pH collectées et sauvegardées.\n");
    printf("Simulation terminée\n");

	// We close files 
    fclose(output2);
    fclose(output3);
    fclose(outputUniques);

	// Here we free the dynamic memory allocation
    free(pollution);
    free(acidite);
    free(sante);

    return 0 ;
}
