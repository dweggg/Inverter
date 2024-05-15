/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAN_e-Tech.c
  * @brief   This file contains functions to handle CAN communication with the car.
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
#include "can.h" // needs can functions and types
#include "INVERTER.h" // needs inverter struct

#include "CAN_e-Tech.h"

// Inverter vars
uint8_t enableCAN;

/**
  * @brief Handle CAN messages.
  *
  * This function implements the logic to handle received CAN messages.
  *
  * @param hcan Pointer to the CAN handle structure.
  */
void handle_CAN(CAN_HandleTypeDef *hcan) {
    // Implement your receive logic here
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];

    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData);

    // Example: Check if the received message ID matches a specific ID
    if (rxHeader.StdId == DBC_INVERTERS_MSG_AP_ETAS_EnableInv.ID) {
        enableCAN = DBC_INVERTERS_MSG_AP_ETAS_EnableInv.getSigVal->Enable_Inv_R;

        // sending a message: move all this to the synchronism message
        float temperatures[] = {inverter_left.temp_inverter, inverter_right.temp_inverter, inverter_left.temp_motor, inverter_right.temp_motor};
        send_CAN_message(hcan, &DBC_INVERTERS_MSG_AP_Inv_R_Temperatures, temperatures);

    }
}

/**
  * @brief Send a CAN message using CAN1db.h information.
  *
  * This function prepares and sends a CAN message using information from CAN1db.h.
  *
  * @param hcan Pointer to the CAN handle structure.
  * @param dbc_msg Pointer to the structure containing CAN message information from CAN1db.h.
  * @param data Pointer to the array of float data to be sent.
  */
void send_CAN_message(CAN_HandleTypeDef *hcan, void *dbc_msg, const float *data) {
    // Extract message information from dbc_msg
    uint32_t id = ((const uint32_t*)dbc_msg)[0];
    uint8_t ide = ((const uint8_t*)dbc_msg)[4];
    uint8_t dlc = ((const uint8_t*)dbc_msg)[5];
    const struct signal_positioned *signals = (const struct signal_positioned*)((const uint8_t*)dbc_msg + 12);

    // Prepare data array
    uint8_t txData[8] = {0};

    // Loop through signals
    for (int i = 0; i < dlc; i++) {
        // Extract signal properties
        uint8_t lengthBits = signals[i].attributes->lengthBits;
        float factor = signals[i].attributes->factor;
        float offset = signals[i].attributes->offset;

        // Convert float data to integer
        uint32_t intData = (uint32_t)((data[i] - offset) / factor);

        // Pack the data into bytes
        for (int j = 0; j < lengthBits / 8; j++) {
            txData[signals[i].position / 8 + j] |= (intData >> (8 * j)) & 0xFF;
        }
    }

    // Prepare CAN header
    CAN_TxHeaderTypeDef txHeader;
    txHeader.StdId = id;
    txHeader.IDE = ide;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = dlc;

    // Send the CAN message
    HAL_CAN_AddTxMessage(hcan, &txHeader, txData, NULL);
}
