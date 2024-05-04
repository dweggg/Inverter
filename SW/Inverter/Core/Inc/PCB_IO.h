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
    LED_MODE_OFF,
    LED_MODE_ON,
    LED_MODE_BLINK_FAST,
    LED_MODE_BLINK_SLOW
} LEDMode;

// Function prototypes
void LED_handler(GPIO_TypeDef *port, uint16_t pin, LEDMode mode, uint32_t ms_counter);


#endif /* PCB_IO_H */
