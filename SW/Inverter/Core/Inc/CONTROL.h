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

/**
 * @brief function.
 *
 * This function calculates the inverse Park transform (irot) and the duty cycles using SVPWM
 *
 * @param vd Voltage in the d-axis.
 * @param vq Voltage in the q-axis.
 * @param vDC DC voltage.
 * @param freq Frequency.
 * @param duties Pointer to the duties structure.
 */
void calc_duties(float vd, float vq, float vDC, float freq, volatile Duties *duties);

#endif /* CONTROL_H */
