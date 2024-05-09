/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    INVERTER.c
  * @brief   Header file for the inverter struct and extern variables.
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
volatile inverterStruct invLeft = {0};

/**
 * @brief Right inverter structure.
 *
 * External declaration of the right inverter structure.
 */
volatile inverterStruct invRight = {0};

/**
 * @brief Raw ADC data for the left inverter.
 *
 * External declaration of raw ADC data for the left inverter.
 */
volatile uint32_t ADC_raw_L[4] = {0};

/**
 * @brief Raw ADC data for the right inverter.
 *
 * External declaration of raw ADC data for the right inverter.
 */
volatile uint32_t ADC_raw_R[4] = {0};

/**
 * @brief Initialize the inverter.
 *
 * This function initializes the inverter structure with the specified LED, GPIO port, and pin.
 *
 * @param inv Pointer to the inverter structure.
 * @param led Pointer to the LED structure.
 * @param enable_port Pointer to the GPIO port for enabling/disabling the inverter.
 * @param enable_pin Pin number for enabling/disabling the inverter.
 * @param htim Timer peripheral for the PWM output.
 * @param hadc ADC peripheral for the current phase current and DC voltage sensing.
 */
void initialize_inverter(volatile inverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc) {
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
