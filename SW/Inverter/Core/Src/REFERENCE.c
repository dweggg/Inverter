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
#include <math.h>
/**
 * @brief Set torque direction based on inverter direction.
 *
 * This function adjusts the torque reference based on the desired direction.
 * If the motor is set to rotate counterclockwise (CCW), positive torque represents braking.
 * If the motor is set to rotate clockwise (CW), positive torque represents traction.
 *
 * @param[in] torque_ref The torque reference value to adjust.
 * @param[in] direction Pointer to the direction of the inverter (1 for CW, -1 for CCW).
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

/**
 * @brief Symmetrically saturate a reference value.
 *
 * This function symmetrically saturates a reference value based on the maximum allowed value.
 * If the reference value exceeds the maximum allowed value, it is saturated to the maximum value.
 * If the reference value is less than the negative of the maximum allowed value, it is saturated to the negative of the maximum value.
 *
 * @param[in] ref The reference value to saturate.
 * @param[in] max_value The maximum allowed value for saturation.
 * @return The saturated reference value.
 */
float saturate_symmetric(float ref, float max_value) {
    if (ref > max_value) {
        return max_value;
    } else if (ref < -max_value) {
        return -max_value;
    } else {
        return ref;
    }
}



/**
 * @brief Speed loop acts as a torque saturation, reducing torque in order to limit the maximum speed.
 * @param[in] speed_max The maximum speed value in RPM.
 * @param[in] speed_meas The measured speed value in RPM.
 * @param[in] torque_ref_pre The torque reference value before this saturation.
 * @param[in] loop_speed Pointer to the speed PI controller structure.
 * @return The limited torque reference value after this saturation.
 */
float limit_torque_to_prevent_overspeed(float speed_max, float speed_meas, float torque_ref_pre, volatile pi_struct *loop_speed){
   // Set speed reference and feedback
	loop_speed->pi_consig = speed_max;
	loop_speed->pi_fdb = fabsf(speed_meas); // Absolute value of speed

    // Initialize and calculate PI controller
    pi_init(loop_speed);
    pi_calc(loop_speed);

    // Calculate limited torque reference based on speed controller output
    float max_torque = loop_speed->pi_out;

    // Limit torque reference within bounds
    float torque_ref;

    if (torque_ref_pre > max_torque) {
        torque_ref = max_torque;
    } else if (torque_ref_pre < -max_torque) {
        torque_ref = -max_torque;
    } else {
        torque_ref = torque_ref_pre;
    }

    return torque_ref;
}


