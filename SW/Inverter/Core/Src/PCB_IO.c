/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    PCB_IO.c
  * @brief   This file provides functions for handling GPIOs and other low-priority tasks.
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
#include "main.h"

// Define LED structures
LED led_left = { .port = LED_LEFT_GPIO_Port, .pin = LED_LEFT_Pin, .mode = LED_MODE_OFF };
LED led_right = { .port = LED_RIGHT_GPIO_Port, .pin = LED_RIGHT_Pin, .mode = LED_MODE_OFF };
LED led_error = { .port = LED_ERR_GPIO_Port, .pin = LED_ERR_Pin, .mode = LED_MODE_OFF };

/**
 * @brief LED handler function.
 *
 * This function handles the LED blinking modes based on the LED mode and current millisecond counter.
 *
 * @param led Pointer to the LED structure.
 * @param ms_counter Current millisecond counter.
 */
void LED_handler(LED *led, uint32_t ms_counter) {
    switch (led->mode) {
        case LED_MODE_BLINK_FAST:
            if (ms_counter % 500 < 250) {
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
