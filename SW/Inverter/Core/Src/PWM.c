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

//	Reset the counter
//	htim->Instance->CNT=0;
	htim->Instance->CCMR1 = 0x6868; // Set Channel 1 and Channel 2 Output Compare mode to PWM Mode

//	htim1.Instance->CCER = 0x888;
	htim->Instance->CCER = 0x10555;

//	Enable Main Output
	htim->Instance->BDTR |=(1<<15);

//	Enable Counter
	htim->Instance->CR1 |=1;

}

/**
 * @brief Disable PWM output.
 *
 * This function disables PWM output for the specified timer.
 *
 * @param htim Pointer to the TIM_HandleTypeDef structure.
 */
void disable_PWM(TIM_HandleTypeDef *htim) {

	//Disable outputs and select the polarity of each output
	htim->Instance->CNT=0;


	htim->Instance->CCER = 0xCCC;
	//	htim1.Instance->CCER |= 0x555;

		//Disable Main Output
	htim->Instance->BDTR &= 0xFFFF7FFF;
	//	htim1.Instance->BDTR &=(0<<15);
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
