/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    INVERTER.h
  * @brief   Header file for the inverter struct and extern variables.
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

#ifndef INVERTER_H
#define INVERTER_H

#include "PCB_IO.h" // peripheral types
#include "MEASUREMENTS.h" // a few structs
#include "REFERENCE.h" // reference struct
#include "MOTOR.h" // motor struct
#include "PWM.h" // duties struct

#include <stdbool.h>


#define TS 0.000025      /**< Switching time in seconds (25 us), inverse of the switching frequency of 40 kHz */
#define DT 0.00000015   /**< Dead time in seconds (150 ns), time in which both top and bottom transistors are open */




/**
 * @brief Enumeration of inverter operation states.
 */
typedef enum {
    INV_STATE_IDLE,    /**< Inverter idle state */
    INV_STATE_STARTUP, /**< Inverter startup state */
    INV_STATE_RUNNING, /**< Inverter running state */
    INV_STATE_FAULT    /**< Inverter fault state */
} InverterState;

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
 * @brief Inverter structure.
 */
typedef struct {
    LED *led;                   /**< Pointer to LED control structure */
    GPIO_TypeDef *enable_port;  /**< Pointer to GPIO port for enabling/disabling the inverter */
    uint16_t enable_pin;        /**< Pin number for enabling/disabling the inverter */
    TIM_HandleTypeDef *htim;    /**< Handle of the timer peripheral for PWM output */
    ADC_HandleTypeDef *hadc;    /**< Handle of the ADC peripheral for current phase currents and DC voltage sensing */
    InverterState state;        /**< Current state of inverter operation */
    Analog analog;  			/**< Structure for phase currents and DC voltage measurements */
    Encoder encoder;            /**< Structure for encoder input */
    Feedback feedback;			/**< Structure for measured currents and calculated mechanical torque and speed */
    Reference reference;		/**< Structure for referece currents and torque */
    Duties duties;              /**< Structure for duty cycles for phases A, B, and C */
    int8_t direction;			/**< Motor direction: 1 CW, -1 CCW, 0 stopped */
    float tempInverter;			/**< Semiconductor temperature in degC */
    float tempMotor;			/**< Motor temperature in degC */
    MotorParameters *motor;		/**< Motor parameters struct */
    pi_struct idLoop;    		/**< PI controller for d-axis current */
    pi_struct iqLoop;   		/**< PI controller for q-axis current */
    float vsMax;				/**< Maximum output voltage, should be calculated as vDC / sqrt3 in volts */
    float vd;					/**< d-axis voltage */
    float vq;					/**< q-axis voltage */
    pi_struct speedLoop;   		/**< PI controller for motor speed */
    InverterError errors;       /**< Error field storing error bits, using InverterError enum */
    bool enable;                /**< Enable bit for transitioning states */
    bool enableSW;              /**< External enable order (needs HW enable to set inv.enable to 1, and if the FAULT state is entered, enableSW must be set to 0 to transition to the IDLE state)  */

} InverterStruct;

extern volatile InverterStruct inverter_left; /**< External declaration of the left inverter structure */
extern volatile InverterStruct inverter_right; /**< External declaration of the right inverter structure */

/**
 * @brief Initialize the inverter.
 *
 * This function initializes the inverter structure with the specified LED, GPIO port, and pin.
 *
 * @param[out] inv Pointer to the inverter structure.
 * @param[in] led Pointer to the LED structure.
 * @param[in] enable_port Pointer to the GPIO port for enabling/disabling the inverter.
 * @param[in] enable_pin Pin number for enabling/disabling the inverter.
 * @param[in] htim Timer peripheral for the PWM output.
 * @param[in] hadc ADC peripheral for the current phase current and DC voltage sensing.
 * @param[in] motor MotorParameters struct.
 */
void initialize_inverter(volatile InverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc, MotorParameters *motor, volatile uint32_t *rawADC);

/**
 * @brief Initializes the id-iq current control PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void init_control_loops(volatile InverterStruct *inv, MotorParameters *motor);

/**
 * @brief Enables the PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void enable_control_loops(volatile InverterStruct *inv);

/**
 * @brief Disables the PI controllers.
 *
 * @param inv Pointer to the inverter structure.
 */
void disable_control_loops(volatile InverterStruct *inv);

/**
 * @brief Sets an error in the inverter's error field.
 * 
 * This function sets the specified error bit in the inverter's error field.
 * 
 * @param[out] inv Pointer to the InverterStruct structure.
 * @param[in] error The error to be set. This should be one of the values from the InverterError enumeration.
 */
void set_error(InverterStruct *inv, InverterError error);

/**
 * @brief Clears an error in the inverter's error field.
 * 
 * This function clears the specified error bit in the inverter's error field.
 * 
 * @param[out] inv Pointer to the InverterStruct structure.
 * @param[in] error The error to be cleared. This should be one of the values from the InverterError enumeration.
 */
void clear_error(InverterStruct *inv, InverterError error);

/**
 * @brief Checks if an error is set in the inverter's error field.
 * 
 * This function checks if the specified error bit is set in the inverter's error field.
 * 
 * @param[in] inv Pointer to the InverterStruct structure.
 * @param[in] error The error to be checked. This should be one of the values from the InverterError enumeration.
 * @return true if the specified error is set, false otherwise.
 */
bool is_error_set(InverterStruct *inv, InverterError error);

#endif /* INVERTER_H */
