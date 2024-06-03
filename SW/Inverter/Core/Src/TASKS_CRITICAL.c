/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TASKS_CRITICAL.c
  * @brief   This file contains functions executed in each PWM timer interruption.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 David Redondo (@dweggg in GitHub).
  * All rights reserved.
  *
  * This software is licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license.
  * For more information, see: https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
  *
  ******************************************************************************
  */

/* USER CODE END Header */

#include "CONTROL.h"
#include "INVERTER.h"
#include <math.h>

uint32_t start_ticks = 0;
uint32_t elapsed_ticks = 0;


angle_struct angle_left = {
    .freq = 0.0F,
    .Ts = TS,
};

rampa_struct freqRamp_left = {
		.in = 5.0F,
		.Incr = TS*1000,
};

/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM1 trigger handler every TS.
 */
void tasks_critical_left(void){
  start_ticks = SysTick->VAL;

  // encoder simulation
  rampa_calc(&freqRamp_left);
  angle_left.freq = freqRamp_left.out;
  angle_calc(&angle_left);

  // put this in encoder function
  inverter_left.encoder.theta_e = angle_left.angle*PI; // angle simulation
  inverter_left.encoder.sinTheta_e = sinf(inverter_left.encoder.theta_e);
  inverter_left.encoder.cosTheta_e = cosf(inverter_left.encoder.theta_e);


  // Actual control loop

  // ADC
  get_currents_voltage(rawADC_left, &inverter_left.analog, &inverter_left.feedback, &inverter_left.errors, inverter_right.encoder.sinTheta_e, inverter_left.encoder.cosTheta_e);
  
  // calculate torque based on measured currents
  inverter_left.feedback.torqueCalc = 1.5F * ((float) inverter_left.motor->pp) * ((inverter_left.motor->Ld - inverter_left.motor->Lq)*inverter_left.feedback.idMeas*inverter_left.feedback.iqMeas + inverter_left.motor->lambda*inverter_left.feedback.iqMeas);
  inverter_left.vsMax = 0.9F * inverter_left.analog.vDC * ISQ3; // Calculate max Vs voltage, 90% of DC/sqrt3
  
  // FOC
  calc_current_reference(inverter_left.motor, &inverter_left.reference);

  // PIs and duty calc
  calc_current_loop(&inverter_left);
  saturate_voltage(&inverter_left);
  calc_duties(inverter_left.vd, inverter_left.vq, inverter_left.analog.vDC, inverter_left.encoder.sinTheta_e, inverter_left.encoder.cosTheta_e, &inverter_left.duties);

  update_PWM(inverter_left.htim, inverter_left.duties);


  elapsed_ticks = start_ticks - SysTick->VAL;

}


/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM8 trigger handler every TS.
 */
void tasks_critical_right(void){
}
