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
#include "REFERENCE.h" // torqueRef and current derating gets calculated in here


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

    // Read direction switch GPIO
    handle_direction(&inverter_left.direction, &inverter_right.direction);

    // Get enableSW via CAN and enableHW from shutdown circuit GPIO reading
    enable_inverters(inverter_left.enableSW, inverter_right.enableSW, &inverter_left.enable, &inverter_right.enable);

    // Acquire temperatures
    inverter_left.tempInverter = get_temperature(rawADC_temp[0], tempInverterLUT);
    inverter_right.tempInverter = get_temperature(rawADC_temp[1], tempInverterLUT);

    inverter_left.tempMotor = get_temperature(rawADC_temp[2], tempMotorLUT);
    inverter_right.tempMotor = get_temperature(rawADC_temp[3], tempMotorLUT);
    
    //TODO: Motor did not have temperature sensor while testing, please delete these lines
    inverter_left.tempMotor = 25.0F;
    inverter_right.tempMotor = 25.0F;



    // Torque reference handling, without ramp
    inverter_left.reference.torqueRef = handle_torqueRef(torqueRefIn_left, inverter_left.direction, inverter_left.motor->torqueMax, inverter_left.motor->speedMax_RPM, inverter_left.feedback.speedMeas, &inverter_left.speedLoop);
    inverter_right.reference.torqueRef = handle_torqueRef(torqueRefIn_right, inverter_right.direction, inverter_right.motor->torqueMax, inverter_right.motor->speedMax_RPM, inverter_right.feedback.speedMeas, &inverter_right.speedLoop);


    // Current reference derating
    inverter_left.reference.isMaxRef = derate_current_reference(inverter_left.tempMotor, inverter_left.tempInverter, inverter_left.motor->iMax);
    inverter_right.reference.isMaxRef = derate_current_reference(inverter_right.tempMotor, inverter_right.tempInverter, inverter_right.motor->iMax);
}
