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
 */
void initialize_inverter(volatile InverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc) {
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

    HAL_TIM_Base_Start_IT(inv->htim);

}
