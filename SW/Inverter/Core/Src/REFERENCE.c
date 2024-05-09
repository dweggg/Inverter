/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    REFERENCE.c
  * @brief   Source file for torque reference handling.
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

#include "REFERENCE.h"

/**
 * @brief Set torque direction based on inverter direction.
 *
 * This function adjusts the torque reference based on the desired direction.
 * If the motor is set to rotate counterclockwise (CCW), positive torque represents braking.
 * If the motor is set to rotate clockwise (CW), positive torque represents traction.
 *
 * @param torque_ref The torque reference value to adjust.
 * @param direction Pointer to the direction of the inverter (1 for CW, -1 for CCW).
 * @return The adjusted torque reference value.
 */
float set_torque_direction(float torque_ref, int8_t direction) {
    float torque_ref_out;

    if (direction == -1) {
        torque_ref_out = -torque_ref; // Adjust torque for counterclockwise rotation
    } else if (direction == 1) {
        torque_ref_out = torque_ref; // Adjust torque for clockwise rotation
    } else {
        torque_ref_out = 0; // No torque adjustment if direction is invalid
    }

    return torque_ref_out;
}
