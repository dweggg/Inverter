#include "PCB_IO.h"
#include "main.h"
// Define LED structures
LED led_left = { .port = LED_LEFT_GPIO_Port, .pin = LED_LEFT_Pin, .mode = LED_MODE_OFF };
LED led_right = { .port = LED_RIGHT_GPIO_Port, .pin = LED_RIGHT_Pin, .mode = LED_MODE_OFF };
LED led_error = { .port = LED_ERR_GPIO_Port, .pin = LED_ERR_Pin, .mode = LED_MODE_OFF };


void LED_handler(LED *led, uint32_t ms_counter) {
    switch (led->mode) {
        case LED_MODE_BLINK_FAST:
            if (ms_counter % 500 < 250) {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            }
            break;
        case LED_MODE_BLINK_SLOW:
            if (ms_counter % 1000 < 500) {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            }
            break;
        case LED_MODE_ON:
            HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
            break;
        case LED_MODE_OFF:
            HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
            break;
        default:
            // Invalid LED mode
            break;
    }
}
