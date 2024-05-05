#ifndef TASKS_1MS_H
#define TASKS_1MS_H

#include <stdint.h>

/**
 * @file TASKS_1ms.h
 * @brief Header file for tasks to be executed every 1ms.
 */

/**
 * @brief Function to be executed every 1ms.
 *
 * This function is called by the TIM6 IRQ handler every millisecond.
 */
void tasks_1ms(void);

#endif /* TASKS_1MS_H */
