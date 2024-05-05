/*
 * TASKS_1ms.c
 *
 *  Created on: May 5, 2024
 *      Author: dwegg
 */

#include "TASKS_1ms.h"
#include "PCB_IO.h"

// Define the ms_counter variable
uint32_t ms_counter = 0;

void tasks_1ms(void) {
    // Increment millisecond counter
    ms_counter++;

    // Call LED handler for left and right LEDs
    LED_handler(&led_left, ms_counter);
    LED_handler(&led_right, ms_counter);
}
