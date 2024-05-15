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


#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

/* Define current and voltage gains/offsets */
#define CURRENT_SLOPE  54.4217687f  /**< [A/V] (10/(4.7+10)) * ( 1 / (12.5 mV / A)) */
#define CURRENT_OFFSET 1.70068027211f /**< [V] (10/(4.7+10))* 2.5 V */
#define VOLTAGE_SLOPE  263.435f  /**< [V/V] 1/(1/3 * 0.011388) V */
#define VOLTAGE_OFFSET 0.02083f /**< [V] (100/(4700+100) * 5 V */

#include <stdint.h>

extern const float tempLUT_inverter[];
extern const float tempLUT_motor[];

extern volatile uint32_t rawADC_left[4]; /**< External declaration of raw ADC data for the left inverter */
extern volatile uint32_t rawADC_right[4]; /**< External declaration of raw ADC data for the right inverter */
extern volatile uint32_t rawADC_temp[4]; /**< External declaration of raw ADC data for the temperatures*/


/**
 * @brief Structure for encoder reading.
 */
typedef struct {
    uint16_t A;       			 /**< Encoder channel A value */
    uint16_t B;       			 /**< Encoder channel B value */
    uint16_t Z;      			 /**< Encoder channel Z value */
    float we;       			 /**< Electrical angular velocity */
    float theta_e; 				 /**< Electrical rotor position */
    float sinTheta_e;			 /**< Electrical rotor position sine */
	float cosTheta_e;			 /**< Electrical rotor position cosine*/
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

/**
  * @brief  Get electrical ADC measurements.
  * @param[in]  ADC_raw Pointer to the raw ADC values array.
  * @param[out]  analog Pointer to the ADC struct to store the results.
  * @param[out] feedback Pointer to the Feedback struct to store id and iq.
  * @param[in] sinTheta_e Electrical angle sine (-1..1)
  * @param[in] cosTheta_e Electrical angle cosine (-1..1)
  * @retval OK 0 if an error occurred, 1 if successful.
  */
uint8_t get_currents_voltage(volatile uint32_t ADC_raw[], volatile Analog* analog, volatile Feedback* feedback, float sinTheta_e, float cosTheta_e);

/**
  * @brief  Convert ADC reading to physical measurement with linear response.
  * @param[in]  bits The ADC reading.
  * @param[in]  slope The slope (volts per unit).
  * @param[in]  offset The offset (volts at zero).
  * @retval measurement The physical measurement.
  */
float get_linear(uint32_t bits, float slope, float offset);

/**
 * @brief Computes d-q currents from current measurements and electrical angle.
 *
 * This function computes the d-q currents from phase currents (ABC), theta_e, and stores
 * the results in the provided pointers.
 *
 * @param[in] ia Phase A current in A.
 * @param[in] ib Phase B current in A.
 * @param[in] ic Phase C current in A.
 * @param[in] sinTheta_e Electrical angle sine (-1..1)
 * @param[in] cosTheta_e Electrical angle cosine (-1..1)
 * @param[out] id_meas Pointer to store the D-axis current.
 * @param[out] iq_meas Pointer to store the Q-axis current.
 */
void get_idiq(float ia, float ib, float ic, float sinTheta_e, float cosTheta_e, float *id_meas, float *iq_meas);


/**
 * @brief Retrieves temperature from a lookup table based on ADC bits.
 *
 * This function retrieves temperature from a lookup table based on the ADC bits.
 * The lookup table (LUT) must have a value for each possible ADC bit combination.
 *
 * @param[in] bits ADC reading converted to bits.
 * @param[in] tempLUT Lookup table containing temperature values.
 * @return Temperature corresponding to the provided ADC bits.
 */
float get_temperature(uint32_t bits, const float tempLUT[]);
#endif /* MEASUREMENTS_H */
