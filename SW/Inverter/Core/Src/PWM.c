/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    PWM.c
  * @brief   This file provides functions for controlling PWM output.
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

#include "PWM.h"

/**
 * @brief Enable PWM output.
 *
 * This function enables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void enable_PWM(TIM_HandleTypeDef *htim) {
    // Enable the main output (MOE)
    __HAL_TIM_MOE_ENABLE(htim);

    // Enable the outputs for all 3 channels
    htim->Instance->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC1NE |
                             TIM_CCER_CC2E | TIM_CCER_CC2NE |
                             TIM_CCER_CC3E | TIM_CCER_CC3NE);
}

/**
 * @brief Disable PWM output.
 *
 * This function disables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void disable_PWM(TIM_HandleTypeDef *htim) {
    // Disable the outputs for all 3 channels
    htim->Instance->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE |
                              TIM_CCER_CC2E | TIM_CCER_CC2NE |
                              TIM_CCER_CC3E | TIM_CCER_CC3NE);
}


/**
 * @brief Set PWM duty cycles.
 *
 * This function sets the duty cycles for the PWM channels.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 * @param duties Duties structure containing duty cycle values.
 */
void update_PWM(TIM_HandleTypeDef *htim, Duties duties) {


	htim->Instance->CCR1 = ((int32_t)(htim->Instance->ARR) * (1.0F-duties.Da));
	htim->Instance->CCR2 = ((int32_t)(htim->Instance->ARR) * (1.0F-duties.Db));
	htim->Instance->CCR3 = ((int32_t)(htim->Instance->ARR) * (1.0F-duties.Dc));

}
