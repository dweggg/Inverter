/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    INVERTER.h
  * @brief   Header file for the inverter struct and extern variables.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 David Redondo (@dweggg on GitHub).
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

#include "PCB_IO.h" // peripheral types
#include "MEASUREMENTS.h" // measurements struct
#include "PWM.h" // duties struct

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
    LED *led;                   /**< Pointer to LED control structure */
    GPIO_TypeDef *enable_port;  /**< Pointer to GPIO port for enabling/disabling the inverter */
    uint16_t enable_pin;        /**< Pin number for enabling/disabling the inverter */
    TIM_HandleTypeDef *htim;    /**< Handle of the timer peripheral for PWM output */
    ADC_HandleTypeDef *hadc;    /**< Handle of the ADC peripheral for current phase currents and DC voltage sensing */
    inverterState state;        /**< Current state of inverter operation */
    Measurements measurements;  /**< Structure for phase currents and DC voltage measurements */
    Encoder encoder;            /**< Structure for ABZ inputs, electrical and mechanical angles and speeds */
    Duties duties;              /**< Structure for duty cycles for phases A, B, and C */
    int8_t direction;			/**< Motor direction: 1 CW, -1 CCW, 0 stopped*/
} inverterStruct;


extern volatile inverterStruct invLeft; /**< External declaration of the left inverter structure */
extern volatile inverterStruct invRight; /**< External declaration of the right inverter structure */

extern volatile uint32_t ADC_raw_L[4]; /**< External declaration of raw ADC data for the left inverter */
extern volatile uint32_t ADC_raw_R[4]; /**< External declaration of raw ADC data for the right inverter */

/**
 * @brief Initialize the inverter.
 *
 * This function initializes the inverter structure with the specified LED, GPIO port, and pin.
 *
 * @param inv Pointer to the inverter structure.
 * @param led Pointer to the LED structure.
 * @param enable_port Pointer to the GPIO port for enabling/disabling the inverter.
 * @param enable_pin Pin number for enabling/disabling the inverter.
 * @param htim Timer peripheral for PWM output.
 * @param hadc ADC peripheral for phase current and DC voltage sensing.
 */
void initialize_inverter(volatile inverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc);


#endif /* INVERTER_H */
