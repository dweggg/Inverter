/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    FSM.h
  * @brief   Header file for Finite State Machine (FSM) control.
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

#ifndef FSM_H
#define FSM_H

#include "INVERTER.h"

/**
 * @brief Run the Finite State Machine (FSM) for inverter operation control.
 *
 * @param inv Pointer to the inverter structure.
 */
void inv_FSM(inverterStruct *inv);

#endif /* FSM_H */
