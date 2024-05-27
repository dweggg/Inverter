/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MEASUREMENTS.h
  * @brief   Header file for handling measurements.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 David Redondo (@dweggg in GitHub).
  * All rights reserved.
  *
  * This software is licensed under the Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license.
  * For more information, see: https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
  *
  ******************************************************************************
  */
/* USER CODE END Header */


#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <stdint.h>

/* Define current and voltage gains/offsets */
#define CURRENT_SLOPE  117.57704f  /**< [A/V] ((4.7+10)/10) * (1 / (12.5 mV / A)) */
#define CURRENT_OFFSET 1.70068027211f /**< [V] (10/(4.7+10))* 2.5 V (not actually used, self calibration at start)*/

#define VOLTAGE_SLOPE  263.435f  /**< [V/V] 1/(1/3 * 0.011388) V */
#define VOLTAGE_OFFSET 0.02083f /**< [V] (100/(4700+100) * 5 V */


/* Define fault thresholds */
#define OVERTEMPERATURE_INVERTER_TH 60.0f /**< [degC] Threshold for inverter overtemperature fault */
#define OVERVOLTAGE_TH 600.0f /**< [V] Threshold for overvoltage fault */
#define OVERCURRENT_TH 100.0f /**< [A] Threshold for instantaneous overcurrent fault */
#define OVERSPEED_TH 20000.0f /**< [RPM] Threshold for motor overspeed fault */
#define UNDERVOLTAGE_TH 10.0f /**< [V] Threshold for undervoltage fault */
#define OVERTEMPERATURE_MOTOR_TH 90.0f /**< [degC] Threshold for motor overtemperature fault */

extern const float tempInverterLUT[];
extern const float tempMotorLUT[];

extern volatile uint16_t rawADC_left[4]; /**< External declaration of raw ADC data for the left inverter */
extern volatile uint16_t rawADC_right[4]; /**< External declaration of raw ADC data for the right inverter */
extern volatile uint16_t rawADC_temp[4]; /**< External declaration of raw ADC data for the temperatures*/


/**
 * @brief Structure for encoder reading.
 */
typedef struct {
    uint16_t A;       			 /**< Encoder channel A value */
    uint16_t B;       			 /**< Encoder channel B value */
    uint16_t Z;      			 /**< Encoder channel Z value */
    float we;       			 /**< Electrical angular velocity */
    float theta_e; 				 /**< Electrical rotor position */
    float sinTheta_e;			 /**< Electrical rotor position sine */
	  float cosTheta_e;			 /**< Electrical rotor position cosine*/
    uint8_t directionMeas;      /**< Measured direction */
} Encoder;


/**
 * @brief Structure for ADC measurements in units.
 */
typedef struct {
    float ia;         			/**< Phase A current in A*/
    float ib;         			/**< Phase B current in A*/
    float ic;         			/**< Phase C current in A*/
    float vDC;        			/**< DC link voltage in V*/
    float currentOffsets[3];	/**< Offsets for the current measurements*/
} Analog;


/**
 * @brief Structure for feedback values.
 */
typedef struct {
    float idMeas;      /**< Measured d-axis current in A*/
    float iqMeas;      /**< Measured q-axis current in A*/
    float torqueCalc;  /**< Calculated torque in N·m*/
    float speedMeas;   /**< Measured speed in RPM*/
} Feedback;


/**
  * @brief  Get electrical ADC measurements.
  * @param[in]  ADC_raw Pointer to the raw ADC values array.
  * @param[out]  analog Pointer to the ADC struct to store the results.
  * @param[out] feedback Pointer to the Feedback struct to store id and iq.
  * @param[in] sinTheta_e Electrical angle sine (-1..1)
  * @param[in] cosTheta_e Electrical angle cosine (-1..1)
  * @retval OK 0 if an error occurred, 1 if successful.
  */
uint8_t get_currents_voltage(volatile uint16_t ADC_raw[], volatile Analog* analog, volatile Feedback* feedback, float sinTheta_e, float cosTheta_e);

/**
  * @brief  Convert ADC reading to physical measurement with linear response.
  * @param[in]  bits The ADC reading.
  * @param[in]  slope The slope (volts per unit).
  * @param[in]  offset The offset (volts at zero).
  * @retval measurement The physical measurement.
  */
float get_linear(uint32_t bits, float slope, float offset);


/**
 * @brief Computes d-q currents from current measurements and electrical angle.
 *
 * This function computes the d-q currents from phase currents (ABC), theta_e, and stores
 * the results in the provided pointers.
 *
 * @param[in] ia Phase A current in A.
 * @param[in] ib Phase B current in A.
 * @param[in] ic Phase C current in A.
 * @param[in] sinTheta_e Electrical angle sine (-1..1)
 * @param[in] cosTheta_e Electrical angle cosine (-1..1)
 * @param[out] idMeas Pointer to store the D-axis current.
 * @param[out] iqMeas Pointer to store the Q-axis current.
 */
void get_idiq(float ia, float ib, float ic, float sinTheta_e, float cosTheta_e, float *idMeas, float *iqMeas);


/**
 * @brief Retrieves temperature from a lookup table based on ADC bits.
 *
 * This function retrieves temperature from a lookup table based on the ADC bits.
 * The lookup table (LUT) must have a value for each possible ADC bit combination.
 *
 * @param[in] bits ADC reading converted to bits.
 * @param[in] tempLUT Lookup table containing temperature values.
 * @return Temperature corresponding to the provided ADC bits.
 */
float get_temperature(uint32_t bits, const float tempLUT[]);


/**
 * @brief Calibrate the current sensor offsets.
 *
 * This function calculates the average offset for each current sensor channel
 * by reading the ADC values when no current is flowing. The calculated offsets
 * are used to correct the sensor readings.
 *
 * @param[in] rawADC Buffer containing the raw ADC values for the channels.
 * @param[out] currentOffsets Array to store the calculated offsets for each current channel.
 * @param[in] numSamples Number of samples to average for the offset calculation.
 */
void calibrate_offsets(volatile uint16_t rawADC[], volatile float currentOffsets[], uint32_t numSamples);


#endif /* MEASUREMENTS_H */
