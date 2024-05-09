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
    float Ld;               /**< D-axis inductance */
    float Lq;               /**< Q-axis inductance */
    float Rs;               /**< Stator resistance */
    float lambda;           /**< Flux linkage */
    int pp;                 /**< Pole pairs */
    float J;                /**< Moment of inertia */
    float b;                /**< Damping factor */
    float torque_max;       /**< Maximum torque */
    float speed_max_RPM;    /**< Maximum speed in RPM */
    float iPhase_pk_max;    /**< Maximum phase current peak value */
    float vDC_max;          /**< Maximum DC bus voltage */
    // Add other parameters as needed
} motorParameters;

#endif /* MOTOR_H */
