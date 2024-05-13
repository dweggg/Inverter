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
/* USER CODE END Header */

/* Define current and voltage gains/offsets */
#define CURRENT_SLOPE  54.4217687f  /**< [A/V] (10/(4.7+10)) * ( 1 / (12.5 mV / A)) */
#define CURRENT_OFFSET 1.70068027211f /**< [V] (10/(4.7+10))* 2.5 V */
#define VOLTAGE_SLOPE  263.435f  /**< [V/V] 1/(1/3 * 0.011388) V */
#define VOLTAGE_OFFSET 0.02083f /**< [V] (100/(4700+100) * 5 V */


#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <stdint.h>

/**
 * @brief Structure for encoder reading.
 */
typedef struct {
    uint16_t A;       			 /**< Encoder channel A value */
    uint16_t B;       			 /**< Encoder channel B value */
    uint16_t Z;      			 /**< Encoder channel Z value */
    float we;       			 /**< Electrical angular velocity */
    float theta_e; 				 /**< Electrical rotor position */
    uint8_t direction_meas;      /**< Measured direction */
} Encoder;

/**
 * @brief Structure for ADC measurements in units.
 */
typedef struct {
    float ia;         /**< Phase A current in A*/
    float ib;         /**< Phase B current in A*/
    float ic;         /**< Phase C current in A*/
    float vDC;        /**< DC link voltage in V*/
} Analog;

/**
 * @brief Structure for feedback values.
 */
typedef struct {
    float id_meas;      /**< Measured d-axis current in A*/
    float iq_meas;      /**< Measured q-axis current in A*/
    float torque_calc;  /**< Calculated torque in N·m*/
    float speed_meas;   /**< Measured speed in RPM*/
} Feedback;

/* Define function prototypes */
/**
  * @brief  Get electrical ADC measurements.
  * @param[in]  ADC_raw Pointer to the raw ADC values array.
  * @param[out]  analog Pointer to the adc struct to store the results.
  * @retval OK 0 if an error occurred, 1 if successful.
  */
uint8_t get_ADC(volatile uint32_t ADC_raw[], volatile Analog* analog);
/**
  * @brief  Convert ADC reading to physical measurement with linear response.
  * @param[in]  bits The ADC reading.
  * @param[in]  slope The slope (volts per unit).
  * @param[in]  offset The offset (volts at zero).
  * @retval measurement The physical measurement.
  */
float get_linear(uint32_t bits, float slope, float offset);


void get_idiq(float ia, float ib, float ic, float theta_e, float *id_meas, float *iq_meas);
#endif /* MEASUREMENTS_H */
