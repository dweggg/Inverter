/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MEASUREMENTS.h
  * @brief   Header file for handling measurements.
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

/* Define current and voltage gains/offsets */
#define CURRENT_SLOPE  54.4217687f  // [A/V] (10/(4.7+10)) * ( 1 A / 12.5 mV)
#define CURRENT_OFFSET 1.70068027211f // [V] (10/(4.7+10))* 2.5 V
#define VOLTAGE_SLOPE  0.003796f  // [V/V] 1/3 * 0.011388 V
#define VOLTAGE_OFFSET 0.02083f // [V] (100/(4700+100) * 5 V

/* USER CODE END Header */
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

/* Include necessary header files */
#include "stm32f7xx_hal.h"
#include <stdint.h>

extern volatile uint32_t ADC_LEFT_raw[4];
extern volatile uint32_t ADC_RIGHT_raw[4];


/* Define encoder struct */
typedef struct {
    uint16_t A;       /**< Encoder channel A value */
    uint16_t B;       /**< Encoder channel B value */
    uint16_t Z;       /**< Encoder channel Z value */
    float wm_rpm;     /**< Mechanical angular velocity (RPM) */
    float we;         /**< Electrical angular velocity */
    float theta_m;    /**< Mechanical rotor position */
    float theta_e;    /**< Electrical rotor position */
    uint8_t DIR;      /**< Direction */
} Encoder;

/* Define measurements struct */
typedef struct {
    float ia;         /**< Phase A current */
    float ib;         /**< Phase B current */
    float ic;         /**< Phase C current */
    float VDC;        /**< DC link voltage */
} Measurements;

/* Declare encoder instances */
extern volatile Encoder encoder_LEFT;
extern volatile Encoder encoder_RIGHT;

/* Declare measurement instances */
extern volatile Measurements measurements_LEFT;
extern volatile Measurements measurements_RIGHT;

/* Define function prototypes */
uint8_t getADCelec(volatile uint32_t* ADC_raw, volatile Encoder* encoder, volatile Measurements* measurements);
float getLinear(uint32_t bits, float slope, float offset);

#endif /* MEASUREMENTS_H */
