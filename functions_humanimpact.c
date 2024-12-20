#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "functions_humanimpact.h"



#define taillex 100     // dimensions of water field
#define tailley 100

double randomDomaine = RAND_MAX + 1.0;   // Domain of randomnumber that we use for the random displacements

//Function to return a number between 1 and max, the parameter that we pass to the function
double randomNumber(double max) {
    return rand() / randomDomaine * max;
}

// This function checks whether a given value (valeur) exists in the array (valeurs).
bool valeurExiste(double *valeurs, int taille, double valeur) {
    for (int i = 0; i < taille; i++) { // Loop through the array.
        if (fabs(valeurs[i] - valeur) < 1e-6) { // Compare with tolerance for floating-point precision.
            return true; // Return true if the value is found.
        }
    }
    return false; // Return false if the value is not found after the loop.
}

// This function finds the index of a given value (valeur) in the array (tableau).
int trouverIndice(double *tableau, int taille, double valeur) {
    for (int i = 0; i < taille; i++) { // Iterate through the array.
        if (fabs(tableau[i] - valeur) < 1e-6) { // Check if the value matches with tolerance.
            return i; // Return the index if a match is found.
        }
    }
    return -1; // Return -1 if the value is not found.
}

// This function collects unique pH values from an array and their associated health data.
int collecterValeursUniquesEtSante(double *ph, double *sante, int taille, 
                                   double *phUniques, double *santeAssociee) {
    int compteur = 0; // Counter to track the number of unique values.

    for (int i = 0; i < taille; i++) { // Iterate through the input pH array.
        int indice = trouverIndice(phUniques, compteur, ph[i]); // Check if the current pH value is already in phUniques.
        
        if (indice == -1) { // If the pH value is unique (not found in phUniques).
            phUniques[compteur] = ph[i]; // Add the unique pH value to the phUniques array.
            santeAssociee[compteur] = sante[i]; // Add the corresponding health data to santeAssociee.
            compteur++; // Increment the counter for unique values.
        }
    }
    return compteur; // Return the total number of unique values collected.
}


// Function to simulate packages of C02
void simulePollution(int x, int y, double r, double c, double * tableau) {
    for (int i = 0; i < 100; i++) {
        double ventX = 5;               // We took values near to values of pollutant ship, to be sure that there is coherant 
        double ventY = 0.3*(x-2);

        double ax = (randomNumber(6) - 3);  // Random movement in direction of x and y axis, due to hazards as a passage of boats, 
        double ay = (randomNumber(6) - 3);

        r = r + 20 / r;                     //Increase of plume, due to wind 

        x += ventX + ax;                //The position of and y are changed for each iteration
        y += ventY + ay;

        //Condition to be sure that the plume not go out of the field
        if ((x < 0 || x >= taillex) || (y < 0 || y >= tailley)) {
            break;
        }

 // Propagation of CO2 over space
        for (int dx = -r; dx <= r; dx++) { // Loop over the x-offsets within the radius r
            for (int dy = -r; dy <= r; dy++) { // Loop over the y-offsets within the radius r
                int nx = x + dx; // Calculate the new x-coordinate
                int ny = y + dy; // Calculate the new y-coordinate

                // Check if the new coordinates (nx, ny) are within the bounds of the grid
                if (nx >= 0 && nx < taillex && ny >= 0 && ny < tailley) { 
                    // Calculate the Euclidean distance from the source point (x, y)
                    double distance = sqrt(dx * dx + dy * dy);

                    // Only proceed if the point is within the radius
                    if (distance <= r) {
                        // Update the value in the grid at position (nx, ny)
                        // The diffusion decreases linearly with the distance from the source
                        tableau[ny * taillex + nx] += c * (1 - distance / r);  
                        // `c` is the coefficient of diffusion, and `(1 - distance / r)` ensures that the closer 
                        // the point is to the source, the greater the contribution to the grid value.
                    }
                }
            }
        }
    }
}

//Function to absorbate some C02 (for exemple algae)

void absorption(double *tableau, int x_taille, int y_taille, double lambda, double delta_t) {
    double decay_factor = exp(-lambda * delta_t);       // Factor in exponential order, find according to data
    for (int i = 0; i < x_taille; i++) {
        for (int j = 0; j < y_taille; j++) {
            tableau[j * x_taille + i] *= decay_factor;
        }
    }
}
