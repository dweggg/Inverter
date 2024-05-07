#include "CONTROL.h"

/**
 * @file control.c
 * @brief Source file for control logic.
 */

// Initialize duties for the left and right sides
Duties duties_LEFT = {0.5f, 0.5f, 0.5f}; /**< Duties for the left side */
Duties duties_RIGHT = {0.5f, 0.5f, 0.5f}; /**< Duties for the right side */

volatile float valfa_L = -0.2F;
volatile float vbeta_L = 0.2F;


/**
 * @brief Control function.
 *
 * This function implements the control logic based on measurements.
 * For now, it sets a constant duty cycle.
 *
 * @param measurements Pointer to the measurements structure.
 * @param duties Pointer to the duties structure.
 */
void control(volatile float valfa, volatile float vbeta, Measurements *measurements, Duties *duties) {


	static svpwm_struct svpwm;

    // Assign values to SVPWM structure
    svpwm.valfa = valfa; // Example value, replace with actual measurement or calculation
    svpwm.vbeta = vbeta; // Example value, replace with actual measurement or calculation

    // Calculate SVPWM
    svpwm_calc(&svpwm);

    // Assign SVPWM duties
    duties->Da = svpwm.Ta;
    duties->Db = svpwm.Tb;
    duties->Dc = svpwm.Tc;
//    duties->Da = 0.5F;
//    duties->Db = 0.5F;
//    duties->Dc = 0.5F;

}
