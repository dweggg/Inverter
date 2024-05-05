/*
 * TASKS_1ms.c
 *
 *  Created on: May 5, 2024
 *      Author: dwegg
 */

#include "TASKS_1ms.h"
#include "PCB_IO.h"

// Define the ms_counter variable
static uint32_t ms_counter = 0;

/**
 * @brief Function to be executed every 1ms.
 *
 * This function is called by the TIM6 IRQ handler every millisecond.
 * It increments the millisecond counter and calls the LED handler
 * for left, right, and error LEDs.
 */
void tasks_1ms(void) {
    // Increment millisecond counter
    ms_counter++;

    // Call LED handler for left, right, and error LEDs
    LED_handler(&led_left, ms_counter);
    LED_handler(&led_right, ms_counter);
    LED_handler(&led_error, ms_counter);
}
