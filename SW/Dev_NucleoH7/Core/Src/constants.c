/*
 * constants.c
 *
 *  Created on: March 9, 2024
 *      Author: dwegg
 */

/**
 * @file constants.c
 * @brief Definition of constants.
 */

// Lookup Table
const int lut_bits[] = {432, 1515, 2230, 2687, 2988, 3190, 3329, 3427, 3497, 3548, 3585, 3614, 3635};
const int lut_temp[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
const int lut_size = sizeof(lut_bits) / sizeof(lut_bits[0]);

const int currentSlope = 12.5e-3; // mV/A
const int currentOffset = 2.5; // V @ 0A

const int voltageSlope = (1/3) * 0.011388; // VDC/VADC (differential)
const int voltageOffset = 0; // V @ 0V


