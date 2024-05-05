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
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);

    Duties duties = {0.5F,0.5F,0.5F};

    set_PWM(htim, &duties);
}

/**
 * @brief Disable PWM output.
 *
 * This function disables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void disable_PWM(TIM_HandleTypeDef *htim) {
    HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_3);
}

/**
 * @brief Set PWM duty cycles.
 *
 * This function sets the duty cycles for the PWM channels.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 * @param duties Pointer to the Duties structure containing duty cycle values.
 */
void set_PWM(TIM_HandleTypeDef *htim, Duties *duties) {
    uint32_t pulse_ch1 = (uint32_t)(duties->Da * __HAL_TIM_GET_AUTORELOAD(htim));
    uint32_t pulse_ch2 = (uint32_t)(duties->Db * __HAL_TIM_GET_AUTORELOAD(htim));
    uint32_t pulse_ch3 = (uint32_t)(duties->Dc * __HAL_TIM_GET_AUTORELOAD(htim));

    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, pulse_ch1);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, pulse_ch2);
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, pulse_ch3);
}
