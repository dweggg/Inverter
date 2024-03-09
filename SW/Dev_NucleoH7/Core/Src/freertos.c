/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Measurements */
osThreadId_t MeasurementsHandle;
const osThreadAttr_t Measurements_attributes = {
  .name = "Measurements",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for qMeasurements */
osMessageQueueId_t qMeasurementsHandle;
const osMessageQueueAttr_t qMeasurements_attributes = {
  .name = "qMeasurements"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void initMeasurements(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of qMeasurements */
  qMeasurementsHandle = osMessageQueueNew (16, sizeof(float), &qMeasurements_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Measurements */
  MeasurementsHandle = osThreadNew(initMeasurements, NULL, &Measurements_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_initMeasurements */
/**
  * @brief  Function implementing the Measurements thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_initMeasurements */
void initMeasurements(void *argument)
{
  /* USER CODE BEGIN initMeasurements */
  /* Infinite loop */
  for(;;)
  {

	// Wait for notification from TIM1 ISR
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

	// Read ADC3 and use getLinear and getTemperature results
	float current = getLinear(Results_ADC3_buffer[0], currentSlope, currentOffset);
	float voltage = getLinear(Results_ADC3_buffer[2], voltageSlope, voltageOffset);
	float temp = getTemperature(Results_ADC3_buffer[1], lut_size, lut_bits, lut_temp);

	// Send to qMeasurements
	osMessageQueuePut(qMeasurementsHandle, &current, 0, 0);
	osMessageQueuePut(qMeasurementsHandle, &voltage, 0, 0);
	osMessageQueuePut(qMeasurementsHandle, &temp, 0, 0);

  }
  /* USER CODE END initMeasurements */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

