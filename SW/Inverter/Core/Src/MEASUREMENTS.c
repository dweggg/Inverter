/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MEASUREMENTS.c
  * @brief   This file provides functions for handling measurements.
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

/* Include necessary header files */
#include "MEASUREMENTS.h"
#include <math.h>
#include <PergaMOD.h>
/**
  * @brief  Get electrical ADC measurements.
  * @param[in]  ADC_raw Pointer to the raw ADC values array.
  * @param[out]  analog Pointer to the ADC struct to store the results.
  * @retval OK 0 if an error occurred, 1 if successful.
  */
uint8_t get_ADC(volatile uint32_t ADC_raw[], volatile Analog* analog) {

    // Calculate currents and voltage
    float ia = get_linear(ADC_raw[0], CURRENT_SLOPE, CURRENT_OFFSET);
    float ib = get_linear(ADC_raw[1], CURRENT_SLOPE, CURRENT_OFFSET);
    float ic = get_linear(ADC_raw[2], CURRENT_SLOPE, CURRENT_OFFSET);
    float vDC = get_linear(ADC_raw[3], VOLTAGE_SLOPE, VOLTAGE_OFFSET);

    // Store the measurements
    analog->ia = ia;
    analog->ib = ib;
    analog->ic = ic;
    analog->vDC = vDC;

    return 1; // Success
}

/**
  * @brief  Convert ADC reading to physical measurement with linear response.
  * @param[in]  bits The ADC reading.
  * @param[in]  slope The slope (units per volt).
  * @param[in]  offset The offset (volts at zero).
  * @retval measurement The physical measurement.
  */
float get_linear(uint32_t bits, float slope, float offset) {
    // Convert ADC reading to voltage
    float voltage = (float) bits * 0.0008058608f; // Assuming 12-bit ADC and 3.3V reference (bits * (3.3 V / 4095.0 bits))

    // Convert voltage to physical measurement
    float measurement = (voltage - offset) * slope;

    return measurement;
}

/**
 * @brief Computes d-q currents from current measurements and electrical angle.
 *
 * This function computes the d-q currents from phase currents (ABC), theta_e, and stores
 * the results in the provided pointers.
 *
 * @param[in] ia Phase A current in A.
 * @param[in] ib Phase B current in A.
 * @param[in] ic Phase C current in A.
 * @param[in] theta_e Electrical rotor position in radians.
 * @param[out] id_meas Pointer to store the D-axis current.
 * @param[out] iq_meas Pointer to store the Q-axis current.
 */
void get_idiq(float ia, float ib, float ic, float theta_e, float *id_meas, float *iq_meas) {

	// Compute alpha beta using Clarke transformation
    float alpha = ia;
    float beta = (ib - ic) * ISQ3;
    // float beta = (ia + 2.0F*ib) * ISQ3;

    // Park transformation
    *id_meas = alpha * cos(theta_e) + beta * sin(theta_e);  // d = alpha * cos(theta_e) + beta * sin(theta_e)
    *iq_meas = beta * cos(theta_e) - alpha * sin(theta_e);  // q = beta * cos(theta_e) - alpha * sin(theta_e)

}

