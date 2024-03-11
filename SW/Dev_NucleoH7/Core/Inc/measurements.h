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
 * @brief Header file for measurement functions.
 */


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
