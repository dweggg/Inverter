#ifndef CONTROL_H
#define CONTROL_H

#include "PWM.h"
#include "MEASUREMENTS.h"
#include "Pergamon_float.h"

/**
 * @file control.h
 * @brief Header file for control logic.
 */

extern float valfa_L;
extern float vbeta_L;


/**
 * @brief Control function.
 *
 * This function implements the control logic based on measurements.
 *
 * @param measurements Measurements structure.
 * @param duties Pointer to the duties structure.
 */
void control(float valfa, float vbeta, Measurements measurements, volatile Duties *duties);

#endif /* CONTROL_H */
