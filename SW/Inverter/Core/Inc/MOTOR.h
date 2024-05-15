/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MOTOR.h
  * @brief   Header file for motor parameters.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 David Redondo (@dweggg on GitHub).
  * All rights reserved.
  *
  * This software is licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license.
  * For more information, see: https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef MOTOR_H
#define MOTOR_H

/**
 * @brief Structure to hold motor parameters
 */
typedef struct {
    float Ld;               /**< D-axis inductance in Henries */
    float Lq;               /**< Q-axis inductance in Henries */
    float Rs;               /**< Stator resistance in Ohms */
    float lambda;           /**< Magnet flux linkage measured V_pk_ph-n · s (phase-neutral peak voltage divided by electrical speed in rad/s) */
    int pp;                 /**< Pole pairs (total number of poles divided by 2) */
    float J;                /**< Rotational inertia in N·m·s^2 */
    float b;                /**< Viscous friction in N·m·s */
    float torque_max;       /**< Maximum torque in N·m */
    float dTorque_max; 		/**< Maximum torque increment in N·m/s */
    float speed_max_RPM;    /**< Maximum speed in RPM */
    float iPhase_pk_max;    /**< Maximum phase current (peak value, or RMS*sqrt2) */
    float vDC_max;          /**< Maximum DC bus voltage in volts */

} MotorParameters;

extern MotorParameters motor_left;
extern MotorParameters motor_right;

/**
  * @brief Perform a parameter check and correct possible errors.
  * @param[in] motor Pointer to the MotorParameters struct.
  * @retval OK 0 if an error occurred, 1 if successful.
  */
int check_motor_parameters(MotorParameters *motor, float Ts);
#endif /* MOTOR_H */
