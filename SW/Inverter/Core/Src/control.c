/*
 * @file control.c
 * @brief Control functions for motor control
 *
 *  Created on: Mar 2, 2024
 *      Author: David Redondo
 *
 *  @brief Control functions for motor control
 */

#include "control.h"
#include "main.h"

/**
 * @brief Implements the voltage control loop.
 *
 * This function calculates the reference current angle for field weakening operation by implementing a PI controller.
 *
 * @param vsRef Synthesized voltage magnitude sqrt(vdRefSat^2+vqRefSat^2)
 * @param gammaRefMTPA Reference current angle MTPA trajectory
 * @param vsLim Voltage limit (VDC/sqrt3)
 * @param[out] gammaRefFW Output reference current angle for field weakening operation from PI
 */

void voltageLoop(float vsRef, float gammaRefMTPA, float vsLim, pi_struct voltageLoop, float *gammaRefFW) {

	voltageLoop.Ts = Ts;
    voltageLoop.pi_out_max = PI - gammaRefMTPA;
    voltageLoop.pi_consig = vsRef;
    voltageLoop.pi_fdb = vsLim * KFW;
    voltageLoop.pi_ffw[0] = 0.0F;  // Feed-forward is not used

    pi_init(&voltageLoop);
    pi_calc(&voltageLoop);

    *gammaRefFW = voltageLoop.pi_out;  // Set the output value
}

/**
 * @brief Implements the current reference calculation.
 *
 * Calculates the d-q current references based on the given parameters.
 *
 * @param TemRefSat Torque reference (after ramp and saturation)
 * @param vsRef Synthesized voltage magnitude sqrt(vdRefSat^2+vqRefSat^2)
 * @param we Electrical speed
 * @param gammaRefFW Reference current angle for field weakening operation from PI
 * @param[out] isRef Reference current magnitude
 * @param[out] gammaRefMTPA Reference current angle MTPA trajectory
 * @param[out] idRef Reference d-axis current
 * @param[out] iqRef Reference q-axis current
 */
void currentRef(float TemRefSat, float vsRef, float we, float gammaRefFW,
                float *isRef, float *gammaRefMTPA, float *idRef, float *iqRef) {
    // Implementation here
}

/**
 * @brief Implements the d-axis current control loop.
 *
 * Calculates the reference d-axis voltage based on given parameters.
 *
 * @param idRef Reference d-axis current
 * @param id Measured d-axis current
 * @param iq Measured q-axis current (for BEMF feed-forward calculation)
 * @param we Electrical speed
 * @param vsLim Voltage limit (VDC/sqrt3)
 * @param vdRefSat Limited reference d-axis voltage for anti-windup
 * @param[out] vdRef Reference d-axis voltage
 * @param[out] Ed d-axis BEMF
 */
void idLoop(float idRef, float id, float iq, float we, float vsLim, float vdRefSat,
            float *vdRef, float *Ed) {
    // Implementation here
}

/**
 * @brief Implements the q-axis current control loop.
 *
 * Calculates the reference q-axis voltage based on given parameters.
 *
 * @param iqRef Reference q-axis current
 * @param iq Measured q-axis current
 * @param id Measured d-axis current (for BEMF feed-forward calculation)
 * @param we Electrical speed
 * @param vsLim Voltage limit (VDC/sqrt3)
 * @param vqRefSat Limited reference q-axis voltage for anti-windup
 * @param[out] vqRef Reference q-axis voltage
 * @param[out] Eq q-axis BEMF
 */
void iqLoop(float iqRef, float iq, float id, float we, float vsLim, float vqRefSat,
            float *vqRef, float *Eq) {
    // Implementation here
}

/**
 * @brief Saturates the output voltages.
 *
 * Ensures that the output voltages are within the specified limits.
 *
 * @param vsLim Voltage limit (VDC/sqrt3)
 * @param vdRef Reference d-axis voltage
 * @param vqRef Reference q-axis voltage
 * @param[out] vdRefSat Limited reference d-axis voltage
 * @param[out] vqRefSat Limited reference q-axis voltage
 */
void voltageSat(float vsLim, float vdRef, float vqRef, float *vdRefSat, float *vqRefSat) {
    // Implementation here
}

/**
 * @brief Converts d-q voltages to space vector modulation duty cycles.
 *
 * Calculates the duty cycles Da, Db, Dc for space vector modulation.
 *
 * @param vdRefSat Limited reference d-axis voltage
 * @param vqRefSat Limited reference q-axis voltage
 * @param vsLim Voltage limit (VDC/sqrt3)
 * @param[out] Da Duty cycle for phase A
 * @param[out] Db Duty cycle for phase B
 * @param[out] Dc Duty cycle for phase C
 */
void dq2SVM(float vdRefSat, float vqRefSat, float vsLim, float *Da, float *Db, float *Dc) {
    // Implementation here
}
