#include "CONTROL.h"

/**
 * @file control.c
 * @brief Source file for control logic.
 */

/**
 * @brief Control function.
 *
 * This function implements the control logic based on measurements.
 * For now, it sets a constant duty cycle.
 *
 * @param measurements Measurements structure.
 * @param duties Pointer to the duties structure.
 */
void control(float alpha, float beta, Measurements measurements, volatile Duties *duties) {


	static svpwm_struct svpwm;

    // Assign values to SVPWM structure
    svpwm.alpha = alpha; // Example value, replace with actual measurement or calculation
    svpwm.beta = beta; // Example value, replace with actual measurement or calculation

    // Calculate SVPWM
    svpwm_calc(&svpwm);

    // Assign SVPWM duties
    duties->Da = svpwm.Da;
    duties->Db = svpwm.Db;
    duties->Dc = svpwm.Dc;

}
