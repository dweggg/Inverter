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

#include "PergaMOD.h" // ramp, pi struct
#include "MOTOR.h" // motor struct
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
 * @brief Handles torque control based on the reference torque, direction, maximum torque, maximum speed, measured speed,
 *        maximum torque rate of change, speed control loop parameters, and sampling time.
 *
 * @param torque_ref_in     Input reference torque.
 * @param direction         Direction of torque (1 for positive torque, -1 for negative torque).
 * @param torque_max        Maximum allowable torque.
 * @param speed_max_RPM     Maximum allowable speed in RPM.
 * @param speed_meas        Measured speed.
 * @param loop_speed        Speed control loop parameters.
 *
 * @return The output torque after handling direction, saturation, and rate limiting.
 */
float handle_torque_ref(float torque_ref_in, int8_t direction, float torque_max, float speed_max_RPM, float speed_meas, volatile pi_struct *loop_speed);

/**
 * @brief Initializes torque ramp
 *
 * @param dTorque_max       Maximum allowable rate of change of torque.
 * @param Ts                Sampling time.
 */
void initialize_torque_ramp(float dTorque_max, float Ts);


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
 * @param[in] torque_ref_in The torque reference value before this saturation.
 * @param[in] loop_speed Pointer to the speed PI controller structure.
 * @return torque_ref_out The limited torque reference value after this saturation.
 */
float limit_torque_to_prevent_overspeed(float speed_max, float speed_meas, float torque_ref_in, volatile pi_struct *loop_speed);

#endif /* REFERENCE_H */
