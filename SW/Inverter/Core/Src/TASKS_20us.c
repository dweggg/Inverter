/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TASKS_20us.c
  * @brief   This file contains functions executed every 20us in each PWM timer interruption.
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

float vd_left = 0.0F;
float vq_left = 100.0F;
float vDC_left = 300.0F;
float freqRef_left = 50.0F;


uint32_t start_ticks = 0;
uint32_t elapsed_ticks = 0;


angle_struct angle_left = {
    .freq = 0.0F,
    .Ts = TS,
};

rampa_struct freqRamp_left = {
		.in = 50.0F,
		.Incr = 5*TS,
};

/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM1 trigger handler every TS.
 */
void tasks_20us_left(void){

  rampa_calc(&freqRamp_left);
  angle_left.freq = freqRamp_left.out;

  angle_calc(&angle_left);
  inverter_left.encoder.theta_e = angle_left.angle*PI; // angle simulation
  inverter_left.encoder.sinTheta_e = sinf(inverter_left.encoder.theta_e);
  inverter_left.encoder.cosTheta_e = cosf(inverter_left.encoder.theta_e);

  start_ticks = SysTick->VAL;

  get_currents_voltage(rawADC_left, &inverter_left.analog, &inverter_left.feedback, inverter_left.encoder.sinTheta_e, inverter_left.encoder.cosTheta_e);
  calc_current_loop(&inverter_left);
  calc_duties(vd_left, vq_left, vDC_left,  inverter_left.encoder.sinTheta_e, inverter_left.encoder.cosTheta_e, &inverter_left.duties);

  elapsed_ticks = start_ticks - SysTick->VAL;

  update_PWM(inverter_left.htim, inverter_left.duties);

}


/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM8 trigger handler every TS.
 */
void tasks_20us_right(void){
}
