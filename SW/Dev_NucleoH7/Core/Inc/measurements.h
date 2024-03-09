/*
 * measurements.h
 *
 *  Created on: March 9, 2024
 *      Author: dwegg
 */

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

/**
 * @file measurements.h
 * @brief Header file for temperature measurement functions.
 */

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
float getTemperature(uint32_t bits, int lut_size, const int lut_bits[], const int lut_temp[]);


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

float getLinear(uint32_t bits, const float slope, const float offset);

#endif /* MEASUREMENTS_H_ */
