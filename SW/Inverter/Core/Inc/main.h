/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "Pergamon_float.h"
#include "config.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Tinv_L_Pin GPIO_PIN_0
#define Tinv_L_GPIO_Port GPIOC
#define Tinv_R_Pin GPIO_PIN_1
#define Tinv_R_GPIO_Port GPIOC
#define Tmot_L_Pin GPIO_PIN_2
#define Tmot_L_GPIO_Port GPIOC
#define Tmot_R_Pin GPIO_PIN_3
#define Tmot_R_GPIO_Port GPIOC
#define ia_L_Pin GPIO_PIN_0
#define ia_L_GPIO_Port GPIOA
#define ib_L_Pin GPIO_PIN_1
#define ib_L_GPIO_Port GPIOA
#define ic_L_Pin GPIO_PIN_2
#define ic_L_GPIO_Port GPIOA
#define VDC_L_Pin GPIO_PIN_3
#define VDC_L_GPIO_Port GPIOA
#define DAC_Pin GPIO_PIN_4
#define DAC_GPIO_Port GPIOA
#define PWM1_R_Pin GPIO_PIN_5
#define PWM1_R_GPIO_Port GPIOA
#define ia_R_Pin GPIO_PIN_6
#define ia_R_GPIO_Port GPIOA
#define ib_R_Pin GPIO_PIN_7
#define ib_R_GPIO_Port GPIOA
#define SC_det_Pin GPIO_PIN_4
#define SC_det_GPIO_Port GPIOC
#define ic_R_Pin GPIO_PIN_0
#define ic_R_GPIO_Port GPIOB
#define VDC_R_Pin GPIO_PIN_1
#define VDC_R_GPIO_Port GPIOB
#define ENABLE_R_Pin GPIO_PIN_2
#define ENABLE_R_GPIO_Port GPIOB
#define ENABLE_L_Pin GPIO_PIN_7
#define ENABLE_L_GPIO_Port GPIOE
#define PWM1_L_Pin GPIO_PIN_8
#define PWM1_L_GPIO_Port GPIOE
#define PWM2_L_Pin GPIO_PIN_9
#define PWM2_L_GPIO_Port GPIOE
#define PWM3_L_Pin GPIO_PIN_10
#define PWM3_L_GPIO_Port GPIOE
#define PWM4_L_Pin GPIO_PIN_11
#define PWM4_L_GPIO_Port GPIOE
#define PWM5_L_Pin GPIO_PIN_12
#define PWM5_L_GPIO_Port GPIOE
#define PWM6_L_Pin GPIO_PIN_13
#define PWM6_L_GPIO_Port GPIOE
#define WRN_L_Pin GPIO_PIN_14
#define WRN_L_GPIO_Port GPIOE
#define WRN_R_Pin GPIO_PIN_15
#define WRN_R_GPIO_Port GPIOE
#define B_R_Pin GPIO_PIN_10
#define B_R_GPIO_Port GPIOB
#define Z_R_Pin GPIO_PIN_11
#define Z_R_GPIO_Port GPIOB
#define PWM3_R_Pin GPIO_PIN_14
#define PWM3_R_GPIO_Port GPIOB
#define PWM5_R_Pin GPIO_PIN_15
#define PWM5_R_GPIO_Port GPIOB
#define A_L_Pin GPIO_PIN_12
#define A_L_GPIO_Port GPIOD
#define B_L_Pin GPIO_PIN_14
#define B_L_GPIO_Port GPIOD
#define Z_L_Pin GPIO_PIN_15
#define Z_L_GPIO_Port GPIOD
#define PWM2_R_Pin GPIO_PIN_6
#define PWM2_R_GPIO_Port GPIOC
#define PWM4_R_Pin GPIO_PIN_7
#define PWM4_R_GPIO_Port GPIOC
#define PWM6_R_Pin GPIO_PIN_8
#define PWM6_R_GPIO_Port GPIOC
#define TRIP_R_Pin GPIO_PIN_9
#define TRIP_R_GPIO_Port GPIOC
#define TRIP_L_Pin GPIO_PIN_8
#define TRIP_L_GPIO_Port GPIOA
#define A_R_Pin GPIO_PIN_15
#define A_R_GPIO_Port GPIOA
#define DIR_Pin GPIO_PIN_3
#define DIR_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_4
#define LED_B_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_5
#define LED_G_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_6
#define LED_R_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
