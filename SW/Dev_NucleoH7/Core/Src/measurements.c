/*
 * measurements.c
 *
 *  Created on: Mar 9, 2024
 *      Author: dwegg
 */

#include "main.h"

/**
 * @brief Calculate temperature using a Look-Up Table (LUT) with linear interpolation.
 *
 * This function finds the temperature corresponding to the given ADC bits using
 * a LUT and linear interpolation.
 *
 * @param bits The ADC bits to convert to temperature.
 * @param lut_size The size of the Look-Up Table (LUT).
 * @param lut_adc Array containing ADC values in the LUT.
 * @param lut_temp Array containing corresponding temperature values in the LUT.
 * @return The temperature corresponding to the ADC bits.
 */


float getTemperature(uint32_t bits, int lut_size, const int lut_bits[], const int lut_temp[]) {
    // Find the closest ADC values in the LUT
    int i;
    for (i = 1; i < lut_size; i++) {
        if (bits < lut_bits[i]) {
            break;
        }
    }

    // Calculate the interpolated temperature
    float adc_diff = lut_bits[i] - lut_bits[i - 1];
    float temp_diff = lut_temp[i] - lut_temp[i - 1];
    float temp = lut_temp[i - 1] + (temp_diff * (bits - lut_bits[i - 1])) / adc_diff;

    return temp;
}


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


