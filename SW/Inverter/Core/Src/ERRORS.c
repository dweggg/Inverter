/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ERRORS.c
  * @brief   This file contains the necessary components to set, read and clear ERRORS.
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

#include "ERRORS.h"

/**
 * @brief Sets an error in the error field of a data structure.
 * 
 * This function sets the specified error bit in the error field of a data structure.
 * 
 * @param[out] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be set. This should be one of the values from the InverterError enumeration.
 */
void set_error(volatile void *data, InverterError error) {
    volatile uint32_t *errors = (volatile uint32_t *)data;
    *errors |= error;
}

/**
 * @brief Clears an error in the error field of a data structure.
 * 
 * This function clears the specified error bit in the error field of a data structure.
 * 
 * @param[out] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be cleared. This should be one of the values from the InverterError enumeration.
 */
void clear_error(volatile void *data, InverterError error) {
    volatile uint32_t *errors = (volatile uint32_t *)data;
    *errors &= ~error;
}

/**
 * @brief Checks if an error is set in the error field of a data structure.
 * 
 * This function checks if the specified error bit is set in the error field of a data structure.
 * 
 * @param[in] data Pointer to the data structure containing the error field.
 * @param[in] error The error to be checked. This should be one of the values from the InverterError enumeration.
 * @return true if the specified error is set, false otherwise.
 */
bool is_error_set(volatile void *data, InverterError error) {
    volatile uint32_t *errors = (volatile uint32_t *)data;
    return (*errors & error) != 0;
}
