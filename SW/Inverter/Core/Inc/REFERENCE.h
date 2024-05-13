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

#include <PergaMOD.h>
#include <stdint.h>

/**
 * @brief Structure for reference values.
 */
typedef struct {
    float id_ref;      /**< Reference d-axis current in A*/
    float iq_ref;      /**< Reference q-axis current in A*/
    float torque_ref;  /**< Reference torque in N·m*/
} Reference;

/**
 * @brief Set torque direction based on inverter direction.
 *
 * This function adjusts the torque reference based on the direction of the inverter.
 * If the inverter is set to rotate counterclockwise (CCW), positive torque represents braking.
 * If the inverter is set to rotate clockwise (CW), positive torque represents traction.
 *
 * @param[in] torque_ref The torque reference value to adjust.
 * @param[in] direction Pointer to the direction of the inverter (1 for CW, -1 for CCW).
 * @return The adjusted torque reference value.
 */
float set_torque_direction(float torque_ref, int8_t direction);

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
float saturate_symmetric(float ref, float max_value);

/**
 * @brief Speed loop acts as a torque saturation, reducing torque in order to limit the maximum speed.
 * @param[in] speed_max The maximum speed value in RPM.
 * @param[in] speed_meas The measured speed value in RPM.
 * @param[in] torque_ref_pre The torque reference value before this saturation.
 * @param[in] loop_speed Pointer to the speed PI controller structure.
 * @return The limited torque reference value after this saturation.
 */
float limit_torque_to_prevent_overspeed(float speed_max, float speed_meas, float torque_ref_pre, volatile pi_struct *loop_speed);

#endif /* REFERENCE_H */
