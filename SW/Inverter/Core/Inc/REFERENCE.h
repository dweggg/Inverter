/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    REFERENCE.h
  * @brief   Header file for torque reference handling.
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

#ifndef REFERENCE_H
#define REFERENCE_H

#include <stdint.h>

/**
 * @brief Structure for reference values.
 */
typedef struct {
    float id_ref;       /**< d-axis current reference in A */
    float iq_ref;       /**< q-axis current reference in A */
    float torque_ref;   /**< Torque reference in N·m */
    float dTorque_max;	/**< Maximum torque increment in N·m/s */
    float speed_max;    /**< Maximum mechanical speed reference in RPM */
} Reference;

/**
 * @brief Set torque direction based on inverter direction.
 *
 * This function adjusts the torque reference based on the direction of the inverter.
 * If the inverter is set to rotate counterclockwise (CCW), positive torque represents braking.
 * If the inverter is set to rotate clockwise (CW), positive torque represents traction.
 *
 * @param torque_ref The torque reference value to adjust.
 * @param direction Pointer to the direction of the inverter (1 for CW, -1 for CCW).
 * @return The adjusted torque reference value.
 */
float set_torque_direction(float torque_ref, int8_t direction);

#endif /* REFERENCE_H */
