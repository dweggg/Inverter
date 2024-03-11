/*
 * constants.h
 *
 *  Created on: March 9, 2024
 *      Author: dwegg
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/**
 * @file constants.h
 * @brief Declaration of constants.
 */

#define DEAD_TIME 240 // 500ns*480MHz
#define FSW 48000 // 480MHz/10kHz

extern const float tempLUT[];

extern const int currentSlope;
extern const int currentOffset;

extern const int voltageSlope;
extern const int voltageOffset;

extern int measurementsAlive;
extern int controlAlive;

#endif /* CONSTANTS_H_ */
