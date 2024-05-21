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
#include "stm32f7xx_hal.h"
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
void initialize_inverter(volatile InverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc, MotorParameters *motor, volatile uint32_t *rawADC){
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

    HAL_ADC_Start_DMA(hadc, (uint32_t *) rawADC, 4);

    HAL_Delay(100);
    calibrate_offsets(rawADC_left, inv->analog.currentOffsets, 50000);


    if(check_motor_parameters(motor, TS)){
        precalculate_motor_constants(motor);
    	init_control_loops(inv, motor);
        inv->state = INV_STATE_IDLE;

    } else{
        inv->state = INV_STATE_FAULT;
    }
}

/**
 * @brief Initializes the PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void init_control_loops(volatile InverterStruct *inv, MotorParameters *motor) {

	// current controllers
    inv->idLoop.Ts = TS;
    inv->iqLoop.Ts = TS;

	float Mp = 0.05; // 5% overshoot
	float set_time = 0.001; // 1ms set time

    // Calculate damping ratio (xi)
    float xi = sqrtf(powf(logf(Mp), 2) / (powf(PI, 2) + powf(logf(Mp), 2))); // Mp is unitless

    // Calculate natural frequency (omega_n)
    float omega_n = 3.0F / (xi * set_time); // set_time in seconds

    // Calculate proportional and integral gains for id controller
    inv->idLoop.Kp = 2.0F * xi * omega_n * motor->Ld - motor->Rs;
    inv->idLoop.Ki = powf(omega_n, 2) * motor->Ld;
    pi_init(&(inv->idLoop)); // Initialize id PI controller (calculate K0, K1)

    // Calculate proportional and integral gains for iq controller
    inv->iqLoop.Kp = 2.0F * xi * omega_n * motor->Lq - motor->Rs;
    inv->iqLoop.Ki = powf(omega_n, 2) * motor->Lq;
    pi_init(&(inv->iqLoop)); // Initialize iq PI controller (calculate K0, K1)


    // speed controller
    inv->speedLoop.Ts = TS;

	float Mp_speed = 0.05; // 5% overshoot
	float set_time_speed = 2; // 2s set time

	float xi_speed = sqrtf(powf(logf(Mp_speed), 2) / (powf(PI, 2) + powf(logf(Mp_speed), 2))); // Mp is unitless
    // Calculate natural frequency (omega_n)
    float omega_n_speed = 3.0F / (xi_speed * set_time_speed); // set_time in seconds

    inv->speedLoop.Kp = 2.0F * xi_speed * omega_n_speed * motor->J - motor->b;
    inv->speedLoop.Ki = powf(omega_n_speed, 2) * motor->J;

    pi_init(&(inv->speedLoop)); // Initialize iq PI controller (calculate K0, K1)

    inv->speedLoop.pi_out_max = motor->torqueMax;
    inv->speedLoop.pi_out_min = -(motor->torqueMax);


}

/**
 * @brief Enables the PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void enable_control_loops(volatile InverterStruct *inv){
	inv->idLoop.enable = 1;
	inv->iqLoop.enable = 1;
	inv->speedLoop.enable = 1;

}

/**
 * @brief Disables the PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void disable_control_loops(volatile InverterStruct *inv){
	inv->idLoop.enable = 0;
	inv->iqLoop.enable = 0;
	inv->speedLoop.enable = 0;
}
