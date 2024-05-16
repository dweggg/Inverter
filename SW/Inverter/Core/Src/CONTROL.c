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

/**
 * @brief Calculates the id-iq currents control actions.
 *
 * @param inv Pointer to the inverter structure.
 */
void calc_current_loop(volatile InverterStruct *inv){

	inv->idLoop.pi_consig = inv->reference.idRef;  	   // Setpoint
    inv->idLoop.pi_fdb = inv->feedback.idMeas;         // Feedback
    pi_calc(&(inv->idLoop));                            // Calculate id PI controller output

    inv->iqLoop.pi_consig = inv->reference.iqRef;  	   // Setpoint
    inv->iqLoop.pi_fdb = inv->feedback.iqMeas;         // Feedback
    pi_calc(&(inv->iqLoop));                            // Calculate iq PI controller output
}

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
void calc_duties(float vd, float vq, float vDC, float sinTheta_e, float cosTheta_e, volatile Duties *duties) {

  // inverse Park transform
  float alpha = (vd/vDC)*cosTheta_e - (vq/vDC)*sinTheta_e;              // Alpha(D) = d*cos(Fi) - q*sin(Fi)
  float beta = (vd/vDC)*sinTheta_e + (vq/vDC)*cosTheta_e;              // Beta(Q) = d*sin(Fi) + q*cos(Fi)


  svpwm_struct svpwm;

  // Assign values to SVPWM structure, works with alpha/beta (not a/b/c)
  // alpha and beta are meant to be in the range +-(1/sqrt3)
  svpwm.alpha = alpha;
  svpwm.beta = beta;
  svpwm_calc(&svpwm);

  // Assign SVPWM duties (0 to 1, high side)
  duties->Da = svpwm.Da;
  duties->Db = svpwm.Db;
  duties->Dc = svpwm.Dc;

}
