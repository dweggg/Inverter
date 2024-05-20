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
    float idRef;      /**< Reference d-axis current in A*/
    float iqRef;      /**< Reference q-axis current in A*/
    float torqueRef;  /**< Reference torque in N·m*/
} Reference;


/**
 * @brief Handles torque control based on the reference torque, direction, maximum torque, maximum speed, measured speed,
 *        maximum torque rate of change, speed control loop parameters, and sampling time.
 *
 * @param torqueRefIn     Input reference torque.
 * @param direction         Direction of torque (1 for positive torque, -1 for negative torque).
 * @param torqueMax        Maximum allowable torque.
 * @param speedMaxRPM     Maximum allowable speed in RPM.
 * @param speedMeas        Measured speed.
 * @param loopSpeed        Speed control loop parameters.
 *
 * @return The output torque after handling direction, saturation, and rate limiting.
 */
float handle_torqueRef(float torqueRefIn, int8_t direction, float torqueMax, float speedMaxRPM, float speedMeas, volatile pi_struct *loopSpeed);


/**
 * @brief Set torque direction based on inverter direction.
 *
 * This function adjusts the torque reference based on the direction of the inverter.
 * If the inverter is set to rotate counterclockwise (CCW), positive torque represents braking.
 * If the inverter is set to rotate clockwise (CW), positive torque represents traction.
 *
 * @param[in] torqueRef The torque reference value to adjust.
 * @param[in] direction Pointer to the direction of the inverter (1 for CW, -1 for CCW).
 * @return The adjusted torque reference value.
 */
float set_torque_direction(float torqueRef, int8_t direction);

/**
 * @brief Symmetrically saturate a reference value.
 *
 * This function symmetrically saturates a reference value based on the maximum allowed value.
 * If the reference value exceeds the maximum allowed value, it is saturated to the maximum value.
 * If the reference value is less than the negative of the maximum allowed value, it is saturated to the negative of the maximum value.
 *
 * @param[in] ref The reference value to saturate.
 * @param[in] max The maximum allowed value for saturation.
 * @return The saturated reference value.
 */
float saturate_symmetric(float ref, float max);

/**
 * @brief Speed loop acts as a torque saturation, reducing torque in order to limit the maximum speed.
 * @param[in] speedMax The maximum speed value in RPM.
 * @param[in] speedMeas The measured speed value in RPM.
 * @param[in] torqueRefIn The torque reference value before this saturation.
 * @param[in] loopSpeed Pointer to the speed PI controller structure.
 * @return torqueRef_out The limited torque reference value after this saturation.
 */
float limit_torque_to_prevent_overspeed(float speedMax, float speedMeas, float torqueRefIn, volatile pi_struct *loopSpeed);

#endif /* REFERENCE_H */
