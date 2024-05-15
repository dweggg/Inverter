/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    INVERTER.c
  * @brief   This file provides code for the inverter struct.
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

#include "INVERTER.h"
#include <math.h>


// Initialize left and right inverters

/**
 * @brief Left inverter structure.
 *
 * External declaration of the left inverter structure.
 */
volatile InverterStruct inverter_left = {0};

/**
 * @brief Right inverter structure.
 *
 * External declaration of the right inverter structure.
 */
volatile InverterStruct inverter_right = {0};

/**
 * @brief Initialize the inverter.
 *
 * This function initializes the inverter structure with the specified LED, GPIO port, and pin.
 *
 * @param[out] inv Pointer to the inverter structure.
 * @param[in] led Pointer to the LED structure.
 * @param[in] enable_port Pointer to the GPIO port for enabling/disabling the inverter.
 * @param[in] enable_pin Pin number for enabling/disabling the inverter.
 * @param[in] htim Timer peripheral for the PWM output.
 * @param[in] hadc ADC peripheral for the current phase current and DC voltage sensing.
 * @param[in] motor MotorParameters struct.
 */
void initialize_inverter(volatile InverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc, MotorParameters *motor) {
    // Initialize inverter structure
    inv->state = INV_STATE_STARTUP;
    inv->led = led;
    inv->enable_pin = enable_pin;
    inv->enable_port = enable_port;
    inv->htim = htim;
    inv->hadc = hadc;
    inv->duties.Da = 0.5;
    inv->duties.Db = 0.5;
    inv->duties.Dc = 0.5;
    inv->motor = motor;

    HAL_TIM_Base_Start_IT(inv->htim);

    if(check_motor_parameters(motor, TS))
    	init_idiq_loops(inv, motor);
    else
        inv->state = INV_STATE_FAULT;

}

/**
 * @brief Initializes the id-iq current control PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void init_idiq_loops(volatile InverterStruct *inv, MotorParameters *motor) {
    inv->id_pi.Ts = TS;
    inv->iq_pi.Ts = TS;

	float Mp = 0.05; // 5% overshoot
	float set_time = 0.001; // 1ms set time

    // Calculate damping ratio (xi)
    float xi = sqrtf(powf(logf(Mp), 2) / (powf(PI, 2) + powf(logf(Mp), 2))); // Mp is unitless

    // Calculate natural frequency (omega_n)
    float omega_n = 3.0F / (xi * set_time); // set_time in seconds

    // Calculate proportional and integral gains for id controller
    inv->id_pi.Kp = 2.0F * xi * omega_n * motor->Ld - motor->Rs;
    inv->id_pi.Ki = powf(omega_n, 2) * motor->Ld;
    pi_init(&(inv->id_pi)); // Initialize id PI controller (calculate K0, K1)

    // Calculate proportional and integral gains for iq controller
    inv->iq_pi.Kp = 2.0F * xi * omega_n * motor->Lq - motor->Rs;
    inv->iq_pi.Ki = powf(omega_n, 2) * motor->Lq;
    pi_init(&(inv->iq_pi)); // Initialize iq PI controller (calculate K0, K1)

}
