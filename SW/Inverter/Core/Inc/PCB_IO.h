/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    PCB_IO.h
  * @brief   Header file for handling GPIOs and other low-priority tasks.
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


#ifndef PCB_IO_H
#define PCB_IO_H

#include "stm32f7xx_hal.h"

// Read SC_det and DIR GPIOs
#define SC_DET_STATE()              (HAL_GPIO_ReadPin(SC_det_GPIO_Port, SC_det_Pin))
#define DIR_STATE()                 (HAL_GPIO_ReadPin(DIR_GPIO_Port, DIR_Pin))

// Read WRN GPIOs
#define WRN_STATE(port, pin)        (HAL_GPIO_ReadPin(port, pin))

// Control ENABLE GPIOs
#define ENABLE(port, pin)           do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET); } while(0)
#define DISABLE(port, pin)          do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET); } while(0)

// Define LED modes
typedef enum {
    LED_MODE_BLINK_FAST, /**< Fast blink mode */
    LED_MODE_BLINK_SLOW, /**< Slow blink mode */
    LED_MODE_ON,         /**< LED on mode */
    LED_MODE_OFF         /**< LED off mode */
} LEDMode;

/**
 * @brief LED structure.
 */
typedef struct {
    GPIO_TypeDef *port; /**< GPIO port for controlling the LED */
    uint16_t pin;       /**< Pin number for controlling the LED */
    LEDMode mode;       /**< Current LED mode */
} LED;

// Declare LED variables as extern
extern LED ledLeft;
extern LED ledRight;
extern LED ledError;

// Function prototypes
/**
 * @brief LED handler function.
 *
 * This function handles the LED blinking modes based on the LED mode and current millisecond counter.
 *
 * @param led Pointer to the LED structure.
 * @param ms_counter Millisecond counter for timing.
 */
void handle_LED(LED *led, uint32_t ms_counter);

/**
 * @brief Handles the direction of the motors.
 *
 * This function reads the state of the DIR switch and updates the directions
 * of both the left and right motors. If one motor is set to rotate
 * clockwise (CW), the other one is set to rotate counterclockwise (CCW),
 * and vice versa.
 *
 * @param dirLeft Pointer to the left inverter direction.
 * @param dirRight Pointer to the right inverter direction.
 */
void handle_direction(volatile int8_t *dirLeft, volatile int8_t *dirRight);

#endif /* PCB_IO_H */
