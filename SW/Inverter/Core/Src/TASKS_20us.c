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


float vd_left = 0.0F;
float vq_left = 100.0F;
float vDC_left = 300.0F;
float freq_left = 50.0F;

angle_struct angle_left = {
    .freq = 0.2F,
    .Ts = TS,
};

/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM1 trigger handler every TS.
 */
void tasks_20us_left(void){


  angle_calc(&angle_left);

  inverter_left.encoder.theta_e = angle_left.angle*PI;

  get_currents_voltage(rawADC_left, &inverter_left.analog);

  calc_duties(vd_left, vq_left, vDC_left, inverter_left.encoder.theta_e, &inverter_left.duties);

  update_PWM(inverter_left.htim, inverter_left.duties);

}


/**
 * @brief Function to be executed every TS.
 *
 * This function is called by the TIM8 trigger handler every TS.
 */
void tasks_20us_right(void){
}
