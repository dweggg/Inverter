/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    PWM.h
  * @brief   Header file for controlling PWM output.
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

#ifndef PWM_H
#define PWM_H

#include "stm32f7xx_hal.h"

/**
 * @brief Structure to hold PWM configuration parameters.
 */
typedef struct {
    float Da; /**< Duty cycle for channel 1 */
    float Db; /**< Duty cycle for channel 2 */
    float Dc; /**< Duty cycle for channel 3 */
} Duties;

/**
 * @brief Enable PWM output.
 *
 * This function enables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void enable_PWM(TIM_HandleTypeDef *htim);

/**
 * @brief Disable PWM output.
 *
 * This function disables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void disable_PWM(TIM_HandleTypeDef *htim);

/**
 * @brief Set PWM duty cycles.
 *
 * This function sets the duty cycles for the PWM channels.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 * @param duties Pointer to the Duties structure containing duty cycle values.
 */
void set_PWM(TIM_HandleTypeDef *htim, Duties *duties);

#endif /* PWM_H */
