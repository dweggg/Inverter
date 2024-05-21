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

#include <stdint.h>

/**
 * @brief Structure to hold precomputed motor constants
 */
typedef struct {
    float threePpLambda;                        /**< 3 * pp * lambda */
    float threePpLdMinusLq;                     /**< 3 * pp * (Ld - Lq) */
    float invThreePpLambda;                     /**< 1 / (3 * pp * lambda) */
    float isc;                                  /**< -lambda / Ld */
    float torqueBase;                           /**< 3 * pp * lambda^2 / Ld */
    float invTorqueBase;                        /**< 1 / (3 * pp * lambda^2 / Ld) */
    float xi;                                   /**< Lq / Ld */
    float xiSquared;                            /**< (Lq / Ld)^2 */
    float oneMinusXi;                           /**< 1 - Lq / Ld */
    float twoMinusXi;                           /**< 2 - Lq / Ld */
    float fourTimesOneMinusXi;                  /**< 4 * (1 - Lq / Ld) */
    float eightTimesOneMinusXiSquared;          /**< 8 * (1 - Lq / Ld)^2 */
    float twoMinusXiSquared;                    /**< (2 - Lq / Ld)^2 */
    float twoTimesOneMinusXiOnePlusXiSquared;   /**< 2 * (1 - Lq / Ld) * (1 + (Lq / Ld)^2) */
    float twoTimesOneMinusXiXiSquared;          /**< 2 * (1 - Lq / Ld) * (Lq / Ld)^2 */
    float fourTimesOneMinusXiOnePlusXiSquared;  /**< 4 * (1 - Lq / Ld) * (1 + (Lq / Ld)^2) */
    float fourTimesOneMinusXiXiSquared;         /**< 4 * (1 - Lq / Ld) * (Lq / Ld)^2 */
    float lambdaDivLqMinusLd;                   /**< lambda / (Lq - Ld) */
    float betaMinusIsc;                         /**< lambda / (Lq - Ld) - lambda / Ld */
} MotorConstants;

/**
 * @brief Structure to hold motor parameters
 */
typedef struct {
    float Ld;                   /**< D-axis inductance in Henries */
    float Lq;                   /**< Q-axis inductance in Henries */
    float Rs;                   /**< Stator resistance in Ohms */
    float lambda;               /**< Magnet flux linkage measured V_pk_ph-n · s (phase-neutral peak voltage divided by electrical speed in rad/s) */
    uint8_t pp;                 /**< Pole pairs (total number of poles divided by 2) */
    float J;                    /**< Rotational inertia in N·m·s^2 */
    float b;                    /**< Viscous friction in N·m·s */
    float torqueMax;            /**< Maximum torque in N·m */
    float dTorqueMax; 		      /**< Maximum torque increment in N·m/s */
    float speedMax_RPM;         /**< Maximum speed in RPM */
    float iMax;                 /**< Maximum phase current (peak value, or RMS*sqrt2) */
    float vDCMax;               /**< Maximum DC bus voltage in volts */
    MotorConstants constants;  /**< Precomputed motor constants */
} MotorParameters;

extern MotorParameters motor_left;
extern MotorParameters motor_right;

/**
 * @brief Precomputes the constants for a motor and updates the MotorParameters structure
 * 
 * @param motor  [in, out] Pointer to the motor parameters structure
 */
void precalculate_motor_constants(MotorParameters* motor);

/**
  * @brief Perform a parameter check and correct possible errors.
  * @param[in] motor Pointer to the MotorParameters struct.
  * @retval OK 0 if an error occurred, 1 if successful.
  */
int check_motor_parameters(MotorParameters *motor, float Ts);
#endif /* MOTOR_H */
