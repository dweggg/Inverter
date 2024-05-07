#ifndef CONTROL_H
#define CONTROL_H

#include "PWM.h"
#include "MEASUREMENTS.h"
#include "Pergamon_float.h"

/**
 * @file control.h
 * @brief Header file for control logic.
 */

extern Duties duties_LEFT; /**< Duties for the left side */
extern Duties duties_RIGHT; /**< Duties for the right side */

extern volatile float valfa_L;
extern volatile float vbeta_L;


/**
 * @brief Control function.
 *
 * This function implements the control logic based on measurements.
 *
 * @param measurements Pointer to the measurements structure.
 * @param duties Pointer to the duties structure.
 */
void control(volatile float valfa, volatile float vbeta, Measurements *measurements, Duties *duties);

#endif /* CONTROL_H */
