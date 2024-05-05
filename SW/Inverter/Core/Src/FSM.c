#include "FSM.h"
#include "PCB_IO.h"

/**
 * @brief FSM state handler for the idle state.
 *
 * This function handles the actions and transitions for the idle state of the inverter operation.
 *
 * @param inv Pointer to the inverter operation structure.
 */
static void idle_handler(InverterOperation *inv);

/**
 * @brief FSM state handler for the startup state.
 *
 * This function handles the actions and transitions for the startup state of the inverter operation.
 *
 * @param inv Pointer to the inverter operation structure.
 */
static void startup_handler(InverterOperation *inv);

/**
 * @brief FSM state handler for the running state.
 *
 * This function handles the actions and transitions for the running state of the inverter operation.
 *
 * @param inv Pointer to the inverter operation structure.
 */
static void running_handler(InverterOperation *inv);

/**
 * @brief FSM state handler for the fault state.
 *
 * This function handles the actions and transitions for the fault state of the inverter operation.
 *
 * @param inv Pointer to the inverter operation structure.
 */
static void fault_handler(InverterOperation *inv);

void inv_init(InverterOperation *inv) {
    // Initialize inverter operation structure
    inv->state = INV_STATE_IDLE;
    // Add initialization of other inverter-specific variables here
}

void inv_FSM(InverterOperation *inv) {
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

static void idle_handler(InverterOperation *inv) {
    // Perform actions required in idle state
    // Transition conditions to other states:
    // - Start startup sequence based on input condition
    // - Transition to fault state based on error conditions
    DISABLE(inv->enable_port, inv->enable_pin);
}

static void startup_handler(InverterOperation *inv) {
    // Perform actions required in startup state
    // Transition conditions to other states:
    // - Transition to running state when startup sequence completes successfully
    // - Transition to fault state based on error conditions during startup
    DISABLE(inv->enable_port, inv->enable_pin);
}

static void running_handler(InverterOperation *inv) {
    // Perform actions required in running state
    // This is where the main control loop resides
    // Monitor inverter variables, adjust control parameters, etc.
    // Transition conditions to other states:
    // - Transition to fault state based on error conditions during operation
    ENABLE(inv->enable_port, inv->enable_pin);
}

static void fault_handler(InverterOperation *inv) {
    // Perform actions required in fault state
    // This could involve shutting down the inverter, logging error messages, etc.
    // Transition conditions to other states:
    // - Retry startup sequence after a delay if fault condition is recoverable
    // - Transition to idle state after fault is resolved
    DISABLE(inv->enable_port, inv->enable_pin);
}
