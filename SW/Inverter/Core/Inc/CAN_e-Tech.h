/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAN_e-Tech.h
  * @brief   Header file for handling CAN communication with the car.
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

#ifndef CAN_E_TECH_H
#define CAN_E_TECH_H

#include "CAN1db.h" // needs the CAN1db and its types

extern uint8_t enableCAN;

typedef struct {
    const uint32_t ID;
    const uint8_t IDE;
    const uint8_t DLC;
    const signal_positioned *getSig;
} CANMessageInfo;

/**
  * @brief Handle CAN messages.
  *
  * This function implements the logic to handle received CAN messages.
  *
  * @param hcan Pointer to the CAN handle structure.
  */
void handle_CAN(CAN_HandleTypeDef *hcan);

/**
  * @brief Send a CAN message using CAN1db.h information.
  *
  * This function prepares and sends a CAN message using information from CAN1db.h.
  *
  * @param hcan Pointer to the CAN handle structure.
  * @param dbc_msg Pointer to the structure containing CAN message information from CAN1db.h.
  * @param data Pointer to the array of float data to be sent.
  */
void send_CAN_message(CAN_HandleTypeDef *hcan, void *dbc_msg, const float *data);

#endif /* CAN_E_TECH_H */
