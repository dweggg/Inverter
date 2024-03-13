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
#include "tim.h"
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
struct Measurement {
  float current;
  float voltage;
  float temp;
};

/* USER CODE END Variables */
/* Definitions for Measurements */
osThreadId_t MeasurementsHandle;
const osThreadAttr_t Measurements_attributes = {
  .name = "Measurements",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Control */
osThreadId_t ControlHandle;
const osThreadAttr_t Control_attributes = {
  .name = "Control",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for qMeasurements */
osMessageQueueId_t qMeasurementsHandle;
const osMessageQueueAttr_t qMeasurements_attributes = {
  .name = "qMeasurements"
};
/* Definitions for qControl */
osMessageQueueId_t qControlHandle;
const osMessageQueueAttr_t qControl_attributes = {
  .name = "qControl"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void initMeasurements(void *argument);
void initControl(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

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

  /* creation of qControl */
  qControlHandle = osMessageQueueNew (16, sizeof(float), &qControl_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Measurements */
  MeasurementsHandle = osThreadNew(initMeasurements, NULL, &Measurements_attributes);

  /* creation of Control */
  ControlHandle = osThreadNew(initControl, NULL, &Control_attributes);

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
  for(;;)
  {
	/* USER CODE BEGIN Measurements task */

	// Wait for notification from Control task
	ulTaskNotifyTake(pdTRUE, 1);

    // Read ADC3 and use getLinear and getTemperature results
    float current = getLinear(ADC3_raw[0], currentSlope, currentOffset);
    float voltage = getLinear(ADC3_raw[2], voltageSlope, voltageOffset);
    float temp = tempLUT[ADC3_raw[1]]; // LUT array indexing

    // Create a struct to hold measurements
    struct Measurement {
      float current;
      float voltage;
      float temp;
    } measurements;

    measurements.current = current;
    measurements.voltage = voltage;
    measurements.temp = temp;

    // Send measurements to qMeasurements
    osMessageQueuePut(qMeasurementsHandle, &measurements, 0, 0);

    measurementsAlive++;

    // Resume Control task
    vTaskResume(ControlHandle);

    // Suspend Measurements task
    vTaskSuspend(NULL);

	/* USER CODE END Measurements task */
  }
}

/* USER CODE BEGIN Header_initControl */
/**
* @brief Function implementing the Control thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_initControl */
void initControl(void *argument)
{
  for(;;)
  {
	/* USER CODE BEGIN Control task */

	// Wait for notification from Measurements task
	ulTaskNotifyTake(pdTRUE, 1);

    // Receive from qMeasurements
    struct Measurement measurements;
    osMessageQueueGet(qMeasurementsHandle, &measurements, 0, 0);

    // Calculate duty based on received current and setpoint
    currentSetpoint = (currentSetpoint < 0.0f) ? 0.0f : (currentSetpoint > 4.0f) ? 4.0f : currentSetpoint;
    float duty = (currentSetpoint - measurements.current) / measurements.voltage;
    duty = 0.5;

    if (enable) {
    	enablePWM(htim1, duty);

    } else {
    	disablePWM(htim1);

    }

    // Send duty to qControl
    osMessageQueuePut(qControlHandle, &duty, 0, 0);

    controlAlive++;

    // Resume Control task
    vTaskResume(MeasurementsHandle);

    // Suspend Measurements task
    vTaskSuspend(NULL);

	/* USER CODE END Control task */

  }
}


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

