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
void initialize_inverter(volatile InverterStruct *inv, LED *led, GPIO_TypeDef *enable_port, uint16_t enable_pin, TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc, MotorParameters *motor);


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

#endif /* INVERTER_H */
