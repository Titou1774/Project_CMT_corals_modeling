#ifndef CORAL_SIMULATION_H
#define CORAL_SIMULATION_H

#include <math.h>

// Constants
#define M_PI 3.14159265358979323846     // Definition of PI

#define T_crit_w 32.5                   // Critical temperature for wrasses
#define T_crit_a 32                     // Critical temperature for anemones
#define T_crit_acropora 30              // Critical temperature for acropora corals
#define T_crit_porites 31               // Critical temperature for porites corals
#define T_crit_other_c 31.5             // Critical temperature for other coral types
#define T_crit_s 31.5                   // Critical temperature for starfish


// Function declarations
void calcule_regression_lineaire(double *temperatures, double *times, int n, double *coefficients);

double temperature(double t, double a, double b, double facteur_climatique);

double facteur_temperature_w(double t, double a, double b, double facteur_climatique);
double facteur_temperature_a(double t, double a, double b, double facteur_climatique);
double facteur_temperature_acropora(double t, double a, double b, double facteur_climatique);
double facteur_temperature_porites(double t, double a, double b, double facteur_climatique);
double facteur_temperature_other_c(double t, double a, double b, double facteur_climatique);
double facteur_temperature_s(double t, double a, double b, double facteur_climatique);


#endif // CORAL_SIMULATION_H
