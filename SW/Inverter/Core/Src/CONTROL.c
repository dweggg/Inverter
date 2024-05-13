/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CONTROL.c
  * @brief   This file provides code for the control loop.
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

#include "CONTROL.h"

#include <math.h> // sin/cos, M_PI
#include <PergaMOD.h> // control functions
#include "INVERTER.h" // TS

/**
 * @brief function.
 *
 * This function calculates the inverse Park transform and the duty cycles using SVPWM
 *
 * @param[in] vd Voltage in the d-axis.
 * @param[in] vq Voltage in the q-axis.
 * @param[in] vDC DC voltage.
 * @param[in] theta_e Electrical angle in radians (-pi..pi).
 * @param[out] duties Pointer to the duties structure.
 */
void calc_duties(float vd, float vq, float vDC, float theta_e, volatile Duties *duties) {


  // inverse Park transform
  float alpha = (vd/vDC)*cosf(theta_e) - (vq/vDC)*sinf(theta_e);              // Alpha(D) = d*cos(Fi) - q*sin(Fi)
  float beta = (vd/vDC)*sinf(theta_e) + (vq/vDC)*cosf(theta_e);              // Beta(Q) = d*sin(Fi) + q*cos(Fi)


  svpwm_struct svpwm;

  // Assign values to SVPWM structure, works with alpha/beta not a/b/c
  svpwm.alpha = alpha;
  svpwm.beta = beta;
  svpwm_calc(&svpwm);

  // Assign SVPWM duties (0 to 1, high side)
  duties->Da = svpwm.Da;
  duties->Db = svpwm.Db;
  duties->Dc = svpwm.Dc;

}
