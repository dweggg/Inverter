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


/**
  * @brief  Get electrical ADC measurements.
  * @param  ADC_raw Pointer to the raw ADC values array.
  * @param  measurements Pointer to the measurements struct to store the results.
  * @retval OK 0 if an error occurred, 1 if successful.
  */
uint8_t getADCelec(volatile uint32_t ADC_raw[], volatile Measurements* measurements) {

    // Calculate currents and voltage
    float ia = getLinear(ADC_raw[0], CURRENT_SLOPE, CURRENT_OFFSET);
    float ib = getLinear(ADC_raw[1], CURRENT_SLOPE, CURRENT_OFFSET);
    float ic = getLinear(ADC_raw[2], CURRENT_SLOPE, CURRENT_OFFSET);
    float VDC = getLinear(ADC_raw[3], VOLTAGE_SLOPE, VOLTAGE_OFFSET);

    // Store the measurements
    measurements->ia = ia;
    measurements->ib = ib;
    measurements->ic = ic;
    measurements->VDC = VDC;

    return 1; // Success
}

/**
  * @brief  Convert ADC reading to physical measurement with linear response.
  * @param  bits The ADC reading.
  * @param  slope The slope (units per volt).
  * @param  offset The offset (volts at zero).
  * @retval measurement The physical measurement.
  */
float getLinear(uint32_t bits, float slope, float offset) {
    // Convert ADC reading to voltage
    float voltage = (float) bits * 0.0008058608f; // Assuming 12-bit ADC and 3.3V reference (bits * (3.3 V / 4095.0 bits))

    // Convert voltage to physical measurement
    float measurement = (voltage - offset) * slope;

    return measurement;
}
