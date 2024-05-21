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

float idRef_left = 0.0F;
float iqRef_left = 0.0F;

float torqueRefIn_left = 0.0F;

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
void tasks_20us_left(void){
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
  get_currents_voltage(rawADC_left, &inverter_left.analog, &inverter_left.feedback, inverter_left.encoder.sinTheta_e, inverter_left.encoder.cosTheta_e);
  inverter_left.vsMax = 0.9F * inverter_left.analog.vDC * ISQ3; // Calculate max Vs voltage, 90% of DC/sqrt3
  
  // Reference generation
  inverter_left.reference.torqueRef = handle_torqueRef(torqueRefIn_left, inverter_left.direction, inverter_left.motor->torqueMax, inverter_left.motor->speedMax_RPM, inverter_left.feedback.speedMeas, &inverter_left.speedLoop);

  // FOC
  calc_current_reference(inverter_left.encoder.we, inverter_left.reference.torqueRef, inverter_left.vsMax, inverter_left.motor, &inverter_left.reference.idRef, &inverter_left.reference.iqRef);

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
void tasks_20us_right(void){
}
