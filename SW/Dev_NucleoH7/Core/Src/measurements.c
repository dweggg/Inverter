/*
 * measurements.c
 *
 *  Created on: Mar 9, 2024
 *      Author: dwegg
 */

#include "main.h"

/**
 * @brief Convert ADC reading to physical measurement with linear response.
 *
 * This function converts an ADC reading to a physical measurement using a linear
 * relationship, considering the slope and offset.
 *
 * @param bits The ADC reading.
 * @param slope The slope (volts per unit).
 * @param offset The offset (volts at zero).
 * @return The physical measurement.
 */
float getLinear(uint32_t bits, float slope, float offset) {
    // Convert ADC reading to voltage
    float voltage = bits * (3.3f / 4095); // Assuming 12-bit ADC and 3.3V reference

    // Convert voltage to physical measurement
    float measurement = (voltage - offset) / slope;

    return measurement;
}


