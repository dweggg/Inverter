/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MOTOR.c
  * @brief   Source file for motor parameters.
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

#include "MOTOR.h"

// May 9th 2024: updated with Mavilor motor parameters (motor located at CITCEA Mec-1 lab)

/**
 * @brief Left motor parameters
 */
motorParameters motorLeft = {
    .Ld = 0.00291,
    .Lq = 0.00295,
    .Rs = 1.95,
    .lambda = 0.13391,
    .pp = 4,
    .J = 0.01,
    .b = 0.001,
    .torque_max = 10.0,
    .speed_max_RPM = 8500.0,
    .iPhase_pk_max = 60.0,
    .vDC_max = 450.0
};

/**
 * @brief Right motor parameters
 */
motorParameters motorRight = {
	    .Ld = 0.00291,
	    .Lq = 0.00295,
	    .Rs = 1.95,
	    .lambda = 0.13391,
	    .pp = 4,
	    .J = 0.01,
	    .b = 0.001,
	    .torque_max = 10.0,
	    .speed_max_RPM = 8500.0,
	    .iPhase_pk_max = 60.0,
	    .vDC_max = 450.0
	};
