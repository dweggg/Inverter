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

#include "CONTROL.h"
#include "Pergamon_float.h" // control functions
#include <math.h> // sin/cos
#include "main.h" // TS

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
void calc_duties(float vd, float vq, float vDC, float freq, volatile Duties *duties) {
	static angle_struct angle;
	angle.freq = freq;
	angle.Ts = TS;
	angle_calc(&angle);

	static irot_struct irot;
	irot.d = vd/vDC;
	irot.q = vq/vDC;
	irot.sinFi = sin(angle.angle*M_TWOPI);
	irot.cosFi = cos(angle.angle*M_TWOPI);
    irot_calc(&irot);

    static svpwm_struct svpwm;
    // Assign values to SVPWM structure
    svpwm.alpha = irot.alpha;
    svpwm.beta = irot.beta;
    svpwm_calc(&svpwm);

    // Assign SVPWM duties
    duties->Da = svpwm.Da;
    duties->Db = svpwm.Db;
    duties->Dc = svpwm.Dc;

}
