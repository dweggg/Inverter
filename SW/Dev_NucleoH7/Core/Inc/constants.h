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

#define DEAD_TIME 0.0000005 // 500ns
#define FSW 10000 // 10kHz

extern volatile float tempLUT[];

extern volatile float currentSlope;
extern volatile float currentOffset;

extern volatile float voltageSlope;
extern volatile float voltageOffset;

extern volatile int measurementsAlive;
extern volatile int controlAlive;
extern volatile int safetyAlive;

#endif /* CONSTANTS_H_ */
