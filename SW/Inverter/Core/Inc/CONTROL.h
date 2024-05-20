/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CONTROL.h
  * @brief   Header file for control logic.
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
 * @brief Calculates the current references [out] based on electrical speed, torque reference, voltage reference,
 *        motor parameters, and updates the d-axis and q-axis current references. Just MTPA for now.
 *
 * @param[in] we         Electrical speed in radians per second.
 * @param[in] torqueRef  Torque reference.
 * @param[in] vsRef      Voltage reference.
 * @param[in] motor      Pointer to the motor parameters structure.
 * @param[out] idRef     Pointer to the d-axis current reference.
 * @param[out] iqRef     Pointer to the q-axis current reference.
 */
void calc_current_reference(float we, float torqueRef, float vsRef, MotorParameters *motor, volatile float * idRef, volatile float * iqRef);

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
