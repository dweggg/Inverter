/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    FSM.c
  * @brief   This file provides code for Finite State Machine (FSM) control.
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

#include "FSM.h"

/**
 * @brief FSM state handler for the idle state.
 *
 * This function handles the actions and transitions for the idle state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
static void idle_handler(volatile inverterStruct *inv);

/**
 * @brief FSM state handler for the startup state.
 *
 * This function handles the actions and transitions for the startup state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
static void startup_handler(volatile inverterStruct *inv);

/**
 * @brief FSM state handler for the running state.
 *
 * This function handles the actions and transitions for the running state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
static void running_handler(volatile inverterStruct *inv);

/**
 * @brief FSM state handler for the fault state.
 *
 * This function handles the actions and transitions for the fault state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
static void fault_handler(volatile inverterStruct *inv);

/**
 * @brief Execute the finite state machine for inverter.
 *
 * This function executes the finite state machine to control the inverter based on its current state.
 *
 * @param inv Pointer to the inverter structure.
 */
void inv_FSM(volatile inverterStruct *inv) {
    switch (inv->state) {
        case INV_STATE_IDLE:
            idle_handler(inv);
            break;
        case INV_STATE_STARTUP:
            startup_handler(inv);
            break;
        case INV_STATE_RUNNING:
            running_handler(inv);
            break;
        case INV_STATE_FAULT:
            fault_handler(inv);
            break;
        default:
            // Invalid state, handle error
            break;
    }
}

/**
 * @brief FSM state handler for the idle state.
 *
 * This function handles the actions and transitions for the idle state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
void idle_handler(volatile inverterStruct *inv) {
    // Perform actions required in idle state
    // Transition conditions to other states:
    // - Start startup sequence based on input condition
    // - Transition to fault state based on error conditions
    inv->led->mode = LED_MODE_OFF;
    DISABLE(inv->enable_port, inv->enable_pin);
}

/**
 * @brief FSM state handler for the startup state.
 *
 * This function handles the actions and transitions for the startup state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
void startup_handler(volatile inverterStruct *inv) {
    // Perform actions required in startup state
    // Transition conditions to other states:
    // - Transition to running state when startup sequence completes successfully
    // - Transition to fault state based on error conditions during startup
    inv->led->mode = LED_MODE_BLINK_FAST;
    DISABLE(inv->enable_port, inv->enable_pin);
}

/**
 * @brief FSM state handler for the running state.
 *
 * This function handles the actions and transitions for the running state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
void running_handler(volatile inverterStruct *inv) {
    // Perform actions required in running state
    // This is where the main control loop resides
    // Monitor inverter variables, adjust control parameters, etc.
    // Transition conditions to other states:
    // - Transition to fault state based on error conditions during operation
    inv->led->mode = LED_MODE_ON;
    ENABLE(inv->enable_port, inv->enable_pin);
}

/**
 * @brief FSM state handler for the fault state.
 *
 * This function handles the actions and transitions for the fault state of the inverter.
 *
 * @param inv Pointer to the inverter structure.
 */
void fault_handler(volatile inverterStruct *inv) {
    // Perform actions required in fault state
    // This could involve shutting down the inverter, logging error messages, etc.
    // Transition conditions to other states:
    // - Retry startup sequence after a delay if fault condition is recoverable
    // - Transition to idle state after fault is resolved
    inv->led->mode = LED_MODE_BLINK_SLOW;
    DISABLE(inv->enable_port, inv->enable_pin);
}
