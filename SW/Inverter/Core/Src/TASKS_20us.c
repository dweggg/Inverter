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


float vd_L = 0.0F;
float vq_L = 100.0F;
float vDC_L = 300.0F;
float freq_L = 50.0F;

angle_struct angle = {
    .freq = 0.2F,
    .Ts = TS,
};
void tasks_20us_LEFT(void){


  angle_calc(&angle);

  invLeft.encoder.theta_e = angle.angle*PI;

  get_currents_voltage(ADC_raw_L, &invLeft.analog);

  calc_duties(vd_L, vq_L, vDC_L, invLeft.encoder.theta_e, &invLeft.duties);

  update_PWM(invLeft.htim, invLeft.duties);

}
