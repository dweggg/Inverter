/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    INVERTER.h
  * @brief   Header file for Finite State Machine (FSM) control.
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

#ifndef INVERTER_H
#define INVERTER_H

#include "stm32f7xx_hal.h"
#include "PCB_IO.h"
#include "MEASUREMENTS.h"
#include "CONTROL.h"

/**
 * @brief Enumeration of inverter operation states.
 */
typedef enum {
    INV_STATE_IDLE,    /**< Inverter idle state */
    INV_STATE_STARTUP, /**< Inverter startup state */
    INV_STATE_RUNNING, /**< Inverter running state */
    INV_STATE_FAULT    /**< Inverter fault state */
} inverterState;


/**
 * @brief Inverter structure.
 */
typedef struct {
    LED *led;                   /**< LED control struct */
    GPIO_TypeDef *enable_port;  /**< GPIO port for enabling/disabling the inverter */
    uint16_t enable_pin;        /**< Pin number for enabling/disabling the inverter */
    TIM_HandleTypeDef *htim;	/**< Handle of the timer peripheral for the PWM output */
    ADC_HandleTypeDef *hadc;	/**< Handle of the ADC peripheral for the current phase currents and DC voltage sensing */
    inverterState state;		/**< Current state of the inverter operation */
    Measurements measurements;	/**< Phase currents and DC voltage measurements*/
    Encoder encoder;			/**< Electrical and mechanical angles and speeds */
    Duties duties;				/**< Duty cycles for phase A,B,C */
} inverterStruct;


extern volatile inverterStruct invLeft;
extern volatile inverterStruct invRight;


extern volatile uint32_t ADC_raw_L[4];
extern volatile uint32_t ADC_raw_R[4];


/**
 * @brief Initialize the inverter.
 *
 * This function initializes the inverter structure with the specified LED, GPIO port, and pin.
 *
 * @param inv Pointer to the inverter structure.
 * @param led Pointer to the LED structure.
 * @param enable_port Pointer to the GPIO port for enabling/disabling the inverter.
 * @param enable_pin Pin number for enabling/disabling the inverter.
 * @param htim Timer peripheral for the PWM output.
 * @param hadc ADC peripheral for the current phase current and DC voltage sensing.

 */
void inv_init(volatile inverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc);


#endif /* INVERTER_H */
