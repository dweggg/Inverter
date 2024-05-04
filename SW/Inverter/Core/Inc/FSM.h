#ifndef FSM_H
#define FSM_H
#include "stm32f7xx_hal.h"

#include <stdbool.h>

/**
 * @file fsm.h
 * @brief Header file for Finite State Machine (FSM) control.
 */

/**
 * @brief Enumeration of inverter states.
 */
typedef enum {
    INV_STATE_IDLE,    /**< Inverter idle state */
    INV_STATE_STARTUP, /**< Inverter startup state */
    INV_STATE_RUNNING, /**< Inverter running state */
    INV_STATE_FAULT    /**< Inverter fault state */
} InverterState;

/**
 * @brief Inverter control structure.
 */
typedef struct {
    InverterState state; /**< Current state of the inverter */

    // GPIO pins for LEDs
    GPIO_TypeDef *LED_port; /**< GPIO port for controlling the LED */
    uint16_t LED_pin; /**< Pin number for controlling the LED */

    // GPIO pin for enable/disable
    GPIO_TypeDef *enable_port; /**< GPIO port for enabling/disabling the inverter */
    uint16_t enable_pin; /**< Pin number for enabling/disabling the inverter */

    // Add any other inverter-specific variables here
} InverterControl;


/**
 * @brief Initialize the inverter control structure.
 *
 * @param inv Pointer to the inverter control structure.
 */
void inv_init(InverterControl *inv);

/**
 * @brief Run the Finite State Machine (FSM) for inverter control.
 *
 * @param inv Pointer to the inverter control structure.
 */
void inv_FSM(InverterControl *inv);

/**
 * @brief FSM state handler for the idle state.
 *
 * @param inv Pointer to the inverter control structure.
 */


#endif /* FSM_H */
