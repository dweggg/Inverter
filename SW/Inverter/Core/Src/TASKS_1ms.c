/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TASKS_1ms.c
  * @brief   This file contains functions to execute tasks every 1ms.
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

#include "TASKS_1ms.h"
#include "PCB_IO.h"		// needs handle functions
#include "INVERTER.h" // needs invLeft/invRight
#include "MEASUREMENTS.h" // needs get_temperature


// Define the ms_counter variable
static uint32_t ms_counter = 0;

/**
 * @brief Function to be executed every 1ms.
 *
 * This function is called by the TIM6 IRQ handler every millisecond.
 * It increments the millisecond counter and executes all the low priority tasks.
 */
void tasks_1ms(void) {
    // Increment millisecond counter
    ms_counter++;

    // Call LED handler for left, right, and error LEDs
    handle_LED(&led_left, ms_counter);
    handle_LED(&led_right, ms_counter);
    handle_LED(&ledError, ms_counter);

    // Read direction switch
    handle_direction(&inverter_left.direction, &inverter_right.direction);


    enable_inverters(inverter_left.enableSW, inverter_right.enableSW, &inverter_left.enable, &inverter_right.enable);


    inverter_left.tempInverter = get_temperature(rawADC_temp[0], tempInverterLUT);
    inverter_right.tempInverter = get_temperature(rawADC_temp[1], tempInverterLUT);
    inverter_left.tempMotor = get_temperature(rawADC_temp[2], tempMotorLUT);
    inverter_right.tempMotor = get_temperature(rawADC_temp[3], tempMotorLUT);

}
