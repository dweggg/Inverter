/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ERRORS.c
  * @brief   Header file for the necessary components to set, read and clear ERRORS.
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
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Enumeration of inverter error states.
 */
typedef enum {
    NONE = 0,
    POWER_FAULT = (1 << 0),           /**< Power fault error bit */
    OVERTEMPERATURE_INV = (1 << 1),   /**< Inverter overtemperature error bit */
    OVERVOLTAGE = (1 << 2),           /**< Overvoltage error bit */
    OVERCURRENT = (1 << 3),           /**< Overcurrent error bit */
    OVERSPEED = (1 << 4),             /**< Overspeed error bit */
    UNDERVOLTAGE = (1 << 5),          /**< Undervoltage error bit */
    CONTROL_FAULT = (1 << 6),         /**< Control fault error bit */
    WARNING = (1 << 7),               /**< Warning error bit */
    OVERTEMPERATURE_MOT = (1 << 8),   /**< Motor overtemperature error bit */
    FEEDBACK_FAULT = (1 << 9)         /**< Feedback fault error bit */
} InverterError;


/**
 * @brief Sets an error in the error field of a data structure.
 * 
 * This function sets the specified error bit in the error field of a data structure.
 * 
 * @param[out] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be set. This should be one of the values from the InverterError enumeration.
 */
void set_error(volatile void *data, InverterError error);

/**
 * @brief Clears an error in the error field of a data structure.
 * 
 * This function clears the specified error bit in the error field of a data structure.
 * 
 * @param[out] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be cleared. This should be one of the values from the InverterError enumeration.
 */
void clear_error(volatile void *data, InverterError error);

/**
 * @brief Checks if an error is set in the error field of a data structure.
 * 
 * This function checks if the specified error bit is set in the error field of a data structure.
 * 
 * @param[in] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be checked. This should be one of the values from the InverterError enumeration.
 * @return true if the specified error is set, false otherwise.
 */
bool is_error_set(volatile void *data, InverterError error);
