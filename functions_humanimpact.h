#ifndef FUNCTIONS_HUMANIMPACT_H
#define FUNCTIONS_HUMANIMPACT_H


#include <stdbool.h> 

// Dimensions of a sea zone, similar to the gilis islands marine park
#define taillex 100
#define tailley 100

extern double randomDomaine;

// Prototypes of functions

/**

 * 
 * @param max 
 * @return 
 */
double randomNumber(double max);

/**
 * Checks if a value already exists in a given array.
 * 
 * @param valeurs 
 * @param taille 
 * @param valeur 
 * @return 
 */
bool valeurExiste(double *valeurs, int taille, double valeur);

/**
 * Find the index of a given value in a table.
 * 
 * @param tableau 
 * @param taille 
 * @param valeur 
 * @return 
 */
int trouverIndice(double *tableau, int taille, double valeur);

/**
 * Collects unique pH values and associated data (coral health).
 * 
 * @param ph 
 * @param sante 
 * @param taille 
 * @param phUniques 
 * @param santeAssociee 
 * @return 
 */
int collecterValeursUniquesEtSante(double *ph, double *sante, int taille, 
                                   double *phUniques, double *santeAssociee);

/**
 * Simulates pollution by C02 packets.
 * 
 * @param x 
 * @param y 
 * @param r 
 * @param c 
 * @param tableau 
 */
void simulePollution(int x, int y, double r, double c, double *tableau);

/**
 * Apply absorption (ex for algae) to pollution.
 * 
 * @param tableau 
 * @param x_taille 
 * @param y_taille 
 * @param lambda 
 * @param delta_t 
 */
void absorption(double *tableau, int x_taille, int y_taille, double lambda, double delta_t);

#endif // FUNCTIONS_HUMANIMPACT_H

