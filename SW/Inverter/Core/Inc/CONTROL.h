/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CONTROL.h
  * @brief   Header file for the control loop.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 David Redondo (@dweggg on GitHub).
  * All rights reserved.
  *
  * This software is licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license.
  * For more information, see: https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
  *
  ******************************************************************************
  */

/* USER CODE END Header */

#ifndef CONTROL_H
#define CONTROL_H

#include "PWM.h" // duties struct
#include "INVERTER.h" // TS & Inverter struct

/**
 * @brief Calculates the current references using a FOC algorithm. It computes the
 * current vector for the MTPA trajectory and limits the current reference to 
 * isMaxRef (calculated by derating, starting from the motor's maximum current).
 * The MTPV trajectory is not implemented to save some computation time due to the
 * nature of the motors expected. In order to implement field weakening, an external
 * voltage loop modifying gammaRef is needed and should be called inside here. When
 * implementing field weakening, special attention must be put to the torque reference 
 * being near 0 or differing from the speed sign (regeneration). A minimum id current
 * must be set for speeds higher than Vs/lambda. Study thoroughly, simulate first.
 * 
 * 
 * @param[in] motor         Pointer to the motor parameters structure.
 * @param[in,out] reference Pointer to the reference struct.
 */
void calc_current_reference(MotorParameters * motor, volatile Reference * reference);

/**
 * @brief Calculates the id-iq loops.
 *
 * @param inv Pointer to the inverter structure.
 */
void calc_current_loop(volatile InverterStruct *inv);

/**
 * @brief Saturates PI output to not surpass DC voltage.
 *
 * @param inv Pointer to the inverter structure.
 */
void saturate_voltage(volatile InverterStruct *inv);

/**
 * @brief function.
 *
 * This function calculates the inverse Park transform and the duty cycles using SVPWM
 *
 * @param[in] vd Voltage in the d-axis.
 * @param[in] vq Voltage in the q-axis.
 * @param[in] vDC DC voltage.
 * @param[in] sinTheta_e Electrical angle sine (-1..1)
 * @param[in] cosTheta_e Electrical angle cosine (-1..1)
 * @param[out] duties Pointer to the duties structure.
 */
void calc_duties(float vd, float vq, float vDC, float sinTheta_e, float cosTheta_e, volatile Duties *duties);

#endif /* CONTROL_H */
