#ifndef PCB_IO_H
#define PCB_IO_H

#include "stm32f7xx_hal.h"

/**
 * @file PCB_IO.h
 * @brief Header file for handling GPIOs and other low-priority tasks.
 */

// Read SC_det and DIR GPIOs
#define SC_DET_STATE()              (HAL_GPIO_ReadPin(SC_det_GPIO_Port, SC_det_Pin))
#define DIR_STATE()                 (HAL_GPIO_ReadPin(DIR_GPIO_Port, DIR_Pin))

// Read WRN GPIOs
#define WRN_STATE(port, pin)        (HAL_GPIO_ReadPin(port, pin))

// Control ENABLE GPIOs
#define ENABLE(port, pin)           do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET); } while(0)
#define DISABLE(port, pin)          do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET); } while(0)

// Define LED modes
typedef enum {
    LED_MODE_BLINK_FAST, /**< Fast blink mode */
    LED_MODE_BLINK_SLOW, /**< Slow blink mode */
    LED_MODE_ON,         /**< LED on mode */
    LED_MODE_OFF         /**< LED off mode */
} LEDMode;

/**
 * @brief LED structure.
 */
typedef struct {
    GPIO_TypeDef *port; /**< GPIO port for controlling the LED */
    uint16_t pin;       /**< Pin number for controlling the LED */
    LEDMode mode;       /**< Current LED mode */
} LED;

// Declare LED variables as extern
extern LED led_left;
extern LED led_right;
extern LED led_error;

// Function prototypes
/**
 * @brief LED handler function.
 *
 * This function handles the LED blinking modes based on the LED mode and current millisecond counter.
 *
 * @param led Pointer to the LED structure.
 * @param ms_counter Millisecond counter for timing.
 */
void LED_handler(LED *led, uint32_t ms_counter);

#endif /* PCB_IO_H */
