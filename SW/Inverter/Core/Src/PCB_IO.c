/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    PCB_IO.c
  * @brief   This file provides functions for handling GPIOs.
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


#include "PCB_IO.h"
#include "main.h" // Pins

// Define LED structures
LED led_left = { .port = LED_LEFT_GPIO_Port, .pin = LED_LEFT_Pin, .mode = LED_MODE_OFF };
LED led_right = { .port = LED_RIGHT_GPIO_Port, .pin = LED_RIGHT_Pin, .mode = LED_MODE_OFF };
LED ledError = { .port = LED_ERR_GPIO_Port, .pin = LED_ERR_Pin, .mode = LED_MODE_OFF };

/**
 * @brief LED handler function.
 *
 * This function handles the LED blinking modes based on the LED mode and current millisecond counter.
 *
 * @param led Pointer to the LED structure.
 * @param ms_counter Current millisecond counter.
 */
void handle_LED(LED *led, uint32_t ms_counter) {
    switch (led->mode) {
        case LED_MODE_BLINK_FAST:
            if (ms_counter % 200 < 100) {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            }
            break;
        case LED_MODE_BLINK_SLOW:
            if (ms_counter % 1000 < 500) {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            }
            break;
        case LED_MODE_ON:
            HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            break;
        case LED_MODE_OFF:
            HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            break;
        default:
            // Invalid LED mode
            break;
    }
}

/**
 * @brief Handles the direction of the motors.
 *
 * This function reads the state of the DIR switch and updates the directions
 * of both the left and right motors. If one motor is set to rotate
 * clockwise (CW), the other one is set to rotate counterclockwise (CCW),
 * and vice versa.
 *
 * @param dir_left Pointer to the direction parameter in the left inverter structure.
 * @param dir_right Pointer to the direction parameter in the right inverter structure.
 */
void handle_direction(volatile int8_t *dir_left, volatile int8_t *dir_right){
	// Read the state of the DIR switch
    GPIO_PinState dirState = HAL_GPIO_ReadPin(DIR_GPIO_Port, DIR_Pin);

    // Update the directions of the inverters based on the DIR switch state
    if (dirState == GPIO_PIN_SET) {
    	*dir_left = 1;  // CW
    	*dir_right = -1;  // CCW
    } else {
    	*dir_left = -1;  // CCW
    	*dir_right = 1;  // CW
    }
}
