#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846     // Definition of PI because M_PI from <math.h> is not recognized by VS Code

#define T_crit_w 32.5                   // Critical temperature for wrasses in the Gili Islands
#define T_crit_a 32                     // Critical temperature for anemones in the Gili Islands
#define T_crit_acropora 30              // Critical temperature for acropora corals in the Gilis Islands
#define T_crit_porites 31               // Critical temperature for porites corals in the Gili Islands
#define T_crit_other_c 31.5             // Critical temperature for other, less temperature-sensitive coral types in the Gili Islands
#define T_crit_s 31.5                   // Critical temperature for starfishs in the Gili Islands

// Function to calculate the linear regression coefficients for temperature data

void calcule_regression_lineaire(double *temperatures, double *times, int n, double *coefficients) {
    
    double sum_t = 0, sum_T = 0, sum_tT = 0, sum_t2 = 0 ;
    
    for (int i = 0 ; i < n ; i++) {
        sum_t += times[i] ;
        sum_T += temperatures[i] ;
        sum_tT += times[i] * temperatures[i] ;
        sum_t2 += times[i] * times[i] ;
    }
    
    double a = (n * sum_tT - sum_t * sum_T) / (n * sum_t2 - sum_t * sum_t) ;  // Slope of the regression line
    double b = (sum_T - a * sum_t) / n ;                                       // Y-intercept at origin
    
    coefficients[0] = a ;   // Store slope
    coefficients[1] = b ;   // Store Y-intercept
}

// Function to calculate temperature at a given time

double temperature(double t, double a, double b, double facteur_climatique) {
    double baseline_temp = a * t + b ;                                          // Base temperature without climate change
    double seasonal_variation = 0.5 * sin(2 * M_PI * t / 12) ;                  // Annual variations
    double climate_trend = facteur_climatique * t ;                             // Increase due to climate change
    return baseline_temp + seasonal_variation + climate_trend ;                 // Total temperature
}

// Wrasses temperature sensitivity

double facteur_temperature_w(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_w = 0.0 ;
    if ( T > T_crit_w) {
        gamma_w = fmin((T - T_crit_w) * 0.1, 1.0) ;                             // Sensitivity with a factor of 0.1
        if (gamma_w > 1) {
            gamma_w = 1.0 ;
        }
        return gamma_w ;
    } else {
        return 0 ;
    }
}

// Anemones temperature sensitivity 

double facteur_temperature_a(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_a = 0.0 ;
    if ( T > T_crit_a) {
        gamma_a = fmin((T - T_crit_a) * 0.1, 1.0) ;  // Sensitivity with a factor of 0.1
        if (gamma_a > 1) {
            gamma_a = 1.0 ;
        }
        return gamma_a ;
    } else {
        return 0 ;
    }
}

// Acropora corals temperature sensitivity

double facteur_temperature_acropora(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_acropora = 0.0 ;
    if ( T > T_crit_acropora) {
        gamma_acropora = fmin((T - T_crit_acropora) * 0.3, 1.0) ;  // Highly sensitive to temperature
        if (gamma_acropora > 1) {
            gamma_acropora = 1.0 ;
        }
        return gamma_acropora ;
    } else {
        return 0 ;
    }
}

// Porites corals temperature sensitivity

double facteur_temperature_porites(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_porites = 0.0 ;
    if ( T > T_crit_porites) {
        gamma_porites = fmin((T - T_crit_porites) * 0.2, 1.0) ;  // Sensitive to temperature
        if (gamma_porites > 1) {
            gamma_porites = 1.0 ;
        }
        return gamma_porites ;
    } else {
        return 0 ;
    }
}

// Other coral types temperature sensitivity

double facteur_temperature_other_c(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_other_c = 0.0 ;
    if ( T > T_crit_other_c) {
        gamma_other_c = fmin((T - T_crit_other_c) * 0.15, 1.0) ;  // Less sensitive to temperature
        if (gamma_other_c > 1) {
            gamma_other_c = 1.0 ;
        }
        return gamma_other_c ;
    } else {
        return 0 ;
    }
}

// Starfish temperature sensitivity

double facteur_temperature_s(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_s = 0.0 ;
    if ( T > T_crit_s) {
        gamma_s = fmin((T - T_crit_s) * 0.1, 1.0) ;  // Sensitivity with a factor of 0.1
        if (gamma_s > 1) {
            gamma_s = 1.0 ;
        }
        return gamma_s ;
    } else {
        return 0 ;
    }
}
