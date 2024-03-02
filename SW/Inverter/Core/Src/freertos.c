/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* Definitions for Measurements_L */
osThreadId_t Measurements_LHandle;
const osThreadAttr_t Measurements_L_attributes = {
  .name = "Measurements_L",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Measurements_R */
osThreadId_t Measurements_RHandle;
const osThreadAttr_t Measurements_R_attributes = {
  .name = "Measurements_R",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Control_L */
osThreadId_t Control_LHandle;
const osThreadAttr_t Control_L_attributes = {
  .name = "Control_L",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Control_R */
osThreadId_t Control_RHandle;
const osThreadAttr_t Control_R_attributes = {
  .name = "Control_R",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for qMeasurements_L */
osMessageQueueId_t qMeasurements_LHandle;
const osMessageQueueAttr_t qMeasurements_L_attributes = {
  .name = "qMeasurements_L"
};
/* Definitions for qMeasurements_R */
osMessageQueueId_t qMeasurements_RHandle;
const osMessageQueueAttr_t qMeasurements_R_attributes = {
  .name = "qMeasurements_R"
};
/* Definitions for qControl_L */
osMessageQueueId_t qControl_LHandle;
const osMessageQueueAttr_t qControl_L_attributes = {
  .name = "qControl_L"
};
/* Definitions for qControl_R */
osMessageQueueId_t qControl_RHandle;
const osMessageQueueAttr_t qControl_R_attributes = {
  .name = "qControl_R"
};
/* Definitions for qTorqueRef_L */
osMessageQueueId_t qTorqueRef_LHandle;
const osMessageQueueAttr_t qTorqueRef_L_attributes = {
  .name = "qTorqueRef_L"
};
/* Definitions for qTorqueRef_R */
osMessageQueueId_t qTorqueRef_RHandle;
const osMessageQueueAttr_t qTorqueRef_R_attributes = {
  .name = "qTorqueRef_R"
};
/* Definitions for qStatus_L */
osMessageQueueId_t qStatus_LHandle;
const osMessageQueueAttr_t qStatus_L_attributes = {
  .name = "qStatus_L"
};
/* Definitions for qStatus_R */
osMessageQueueId_t qStatus_RHandle;
const osMessageQueueAttr_t qStatus_R_attributes = {
  .name = "qStatus_R"
};
/* Definitions for qTemperatures */
osMessageQueueId_t qTemperaturesHandle;
const osMessageQueueAttr_t qTemperatures_attributes = {
  .name = "qTemperatures"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void startMeasurements(void *argument);
void startControl(void *argument);

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
  /* creation of qMeasurements_L */
  qMeasurements_LHandle = osMessageQueueNew (16, sizeof(float), &qMeasurements_L_attributes);

  /* creation of qMeasurements_R */
  qMeasurements_RHandle = osMessageQueueNew (16, sizeof(float), &qMeasurements_R_attributes);

  /* creation of qControl_L */
  qControl_LHandle = osMessageQueueNew (16, sizeof(float), &qControl_L_attributes);

  /* creation of qControl_R */
  qControl_RHandle = osMessageQueueNew (16, sizeof(float), &qControl_R_attributes);

  /* creation of qTorqueRef_L */
  qTorqueRef_LHandle = osMessageQueueNew (16, sizeof(float), &qTorqueRef_L_attributes);

  /* creation of qTorqueRef_R */
  qTorqueRef_RHandle = osMessageQueueNew (16, sizeof(float), &qTorqueRef_R_attributes);

  /* creation of qStatus_L */
  qStatus_LHandle = osMessageQueueNew (16, sizeof(float), &qStatus_L_attributes);

  /* creation of qStatus_R */
  qStatus_RHandle = osMessageQueueNew (16, sizeof(float), &qStatus_R_attributes);

  /* creation of qTemperatures */
  qTemperaturesHandle = osMessageQueueNew (16, sizeof(float), &qTemperatures_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Measurements_L */
  Measurements_LHandle = osThreadNew(startMeasurements, NULL, &Measurements_L_attributes);

  /* creation of Measurements_R */
  Measurements_RHandle = osThreadNew(startMeasurements, NULL, &Measurements_R_attributes);

  /* creation of Control_L */
  Control_LHandle = osThreadNew(startControl, NULL, &Control_L_attributes);

  /* creation of Control_R */
  Control_RHandle = osThreadNew(startControl, NULL, &Control_R_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_startMeasurements */
/**
  * @brief  Function implementing the Measurements_L thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_startMeasurements */
void startMeasurements(void *argument)
{
  /* USER CODE BEGIN startMeasurements */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startMeasurements */
}

/* USER CODE BEGIN Header_startControl */
/**
* @brief Function implementing the Control_L thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startControl */
void startControl(void *argument)
{
  /* USER CODE BEGIN startControl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END startControl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

