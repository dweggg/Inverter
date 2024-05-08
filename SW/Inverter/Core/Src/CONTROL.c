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
void control(float valfa, float vbeta, Measurements measurements, volatile Duties *duties) {


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

}
