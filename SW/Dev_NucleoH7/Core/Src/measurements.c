/*
 * measurements.c
 *
 *  Created on: Mar 9, 2024
 *      Author: dwegg
 */

#include "main.h"

/**
 * @brief Convert ADC reading to physical measurement with linear response.
 *
 * This function converts an ADC reading to a physical measurement using a linear
 * relationship, considering the slope and offset.
 *
 * @param bits The ADC reading.
 * @param slope The slope (volts per unit).
 * @param offset The offset (volts at zero).
 * @return The physical measurement.
 */
float getLinear(uint32_t bits, float slope, float offset) {
    // Convert ADC reading to voltage
    float voltage = bits * (3.3f / 4095); // Assuming 12-bit ADC and 3.3V reference

    // Convert voltage to physical measurement
    float measurement = (voltage - offset) / slope;

    return measurement;
}


void enablePWM(TIM_HandleTypeDef htimX, float duty){

	//Reset the counter
	htimX.Instance->CNT=0;

	htimX.Instance->CCMR1 = 0x6868; // Set Channel 1 and Channel 2 Output Compare mode to PWM Mode

	//	htim1.Instance->CCER = 0x888;
	htimX.Instance->CCER = 0x10555;

	//Enable Main Output
	htimX.Instance->BDTR |=(1<<15);

	//Enable Counter
	htimX.Instance->CR1 |=1;

	htimX.Instance->CCR1 = (duty)*htimX.Instance->ARR;
	htimX.Instance->CCR2 = (1-duty)*htimX.Instance->ARR;

}

void disablePWM(TIM_HandleTypeDef htimX){

	//Disable outputs and select the polarity of each output

	htimX.Instance->CNT=0;

	//	htim1.Instance->CCER = 0x888;
	htimX.Instance->CCER = 0xCCC;
	//	htim1.Instance->CCER |= 0x555;

	//Disable Main Output
	htimX.Instance->BDTR &= 0xFFFF7FFF;
	//	htim1.Instance->BDTR &=(0<<15);

	//Disable Counter (No se si es necesario)
	htimX.Instance->CR1 |=1;
}
