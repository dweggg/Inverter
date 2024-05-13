/*
 * @file PergaMOD.c
 * @brief Library consolidating all the hardware-independent libraries of CITCEA.
 * This library is based on Alexandria created by Gabriel Gross and Quim Lopez Mestre in September 2006.
 * Created by Gabriel Gross, Daniel Heredero, and Tomas Lledo in December 2015.
 * Translated to floats by Lucas Bouzon in March 2020.
 */

/*
                       ____                      __  __  ___  ____
                      |  _ \ ___ _ __ __ _  __ _|  \/  |/ _ \|  _ \  ___
                      | |_) / _ \ '__/ _` |/ _` | |\/| | | | | | | |/ __|
                      |  __/  __/ | | (_| | (_| | |  | | |_| | |_| | (__
                      |_|   \___|_|  \__, |\__,_|_|  |_|\___/|____(_)___|
                                     |___/
*/

#include <math.h>
#include <PergaMOD.h>

// PI amb el nou antiwindup
//=========================================================================
/**
 * @brief Calculates the Proportional-Integral (PI) control with anti-windup.
 *
 * @param v Pointer to the PI control structure.
 *
 * @note This function computes the PI control action with anti-windup.
 */
void pi_aw_calc(volatile pi_aw_struct *v)
{
    if(v->enable)
    {
        v->e[0] = v->pi_consig - v->pi_fdb; // Calculate error

        // PI trapezoidal with feedforward
        v->pi_int[0] =  v->Ki * v->e[0] * v->Ts + v->pi_int[1] + (v->pi_out_postsat - v->pi_out_presat) * v->Kaw * v->Ts;

        v->pi_out_presat = v->pi_out;

        // Output voltage saturation
        if (v->pi_out > v->pi_out_max)
            v->pi_out = v->pi_out_max;
        else if (v->pi_out < v->pi_out_min)
            v->pi_out = v->pi_out_min;
        else;

        // Copy previous values
        v->e[1] = v->e[0];                      // Copy previous error
        v->pi_ffw[1] = v->pi_ffw[0];            // Copy previous feedforward
        v->pi_int[1] = v->pi_int[0];			// Copy previous integrator
    }
    else
    {
        // Reset previous control variables
        v->e[1] = 0.0F;
        v->pi_ffw[1] = 0.0F;
        v->pi_int[1] = 0.0F;
        v->pi_out = 0.0F;
    }
}

// PI
//=========================================================================
// Initialize PI constants
/**
 * @brief Initializes the constants of the Proportional-Integral (PI) controller.
 *
 * @param v Pointer to the PI structure.
 *
 * @note This function initializes the constants used in the PI controller.
 */
void pi_init(volatile pi_struct *v){
    v->K0 = v->Kp + v->Ki * v->Ts * 0.5F;   // K0 = Kp + Ki*Ts/2
    v->K1 = -v->Kp + v->Ki * v->Ts * 0.5F;  // K1 = -Kp + Ki*Ts/2
}

// PI with feedforward and saturation
/**
 * @brief Calculates the Proportional-Integral (PI) control action with feedforward and saturation.
 *
 * @param v Pointer to the PI structure.
 *
 * @note This function computes the PI control action with feedforward and saturation.
 */
void pi_calc(volatile pi_struct *v)
{
    if(v->enable)
    {
        v->e[0] = v->pi_consig - v->pi_fdb; // Calculate error
        v->pi_out += v->K0 * v->e[0] + v->K1 * v->e[1] + v->pi_ffw[0] - v->pi_ffw[1];   // PI trapezoidal with feedforward
        // Output voltage saturation
        if (v->pi_out > v->pi_out_max)
            v->pi_out = v->pi_out_max;
        else if (v->pi_out < v->pi_out_min)
            v->pi_out = v->pi_out_min;
        else;
        // Copy previous values
        v->e[1] = v->e[0];                      // Copy previous error
        v->pi_ffw[1] = v->pi_ffw[0];            // Copy previous feedforward
    }
    else
    {
        // Reset previous control variables
        v->e[1] = 0.0F;
        v->pi_ffw[1] = 0.0F;
        v->pi_out = 0.0F;
    }
}

// PI without saturation for external saturation
/**
 * @brief Calculates the Proportional-Integral (PI) control action without saturation for external saturation.
 *
 * @param v Pointer to the PI structure.
 *
 * @note This function computes the PI control action without saturation for external saturation.
 */
void pi_extsat_calc(volatile pi_struct *v)
{
    if(v->enable)
    {
        v->e[0] = v->pi_consig - v->pi_fdb; // Calculate error
        v->pi_out += v->K0 * v->e[0] + v->K1 * v->e[1] + v->pi_ffw[0] - v->pi_ffw[1];   // PI trapezoidal with feedforward
        // Copy previous values
        v->e[1] = v->e[0];                      // Copy previous error
        v->pi_ffw[1] = v->pi_ffw[0];            // Copy previous feedforward
    }
    else
    {
        // Reset previous control variables
        v->e[1] = 0.0F;
        v->pi_ffw[1] = 0.0F;
        v->pi_out = 0.0F;
    }
}

// CLARKE 3F
//=========================================================================
/**
 * @brief Calculates the Clarke transformation for three-phase signals.
 *
 * @param v Pointer to the Clarke transformation structure.
 *
 * @note This function computes the Clarke transformation for three-phase signals.
 */
void clarke3F_calc(volatile clarke3F_struct *v)
{
    v->D = v->a;                                       // Alfa = A
    v->Q = ISQ3*( v->a + 2.0F * v->b );              // Beta = 1/sqrt(3)*(A + 2*B) = 1/sqrt(3)*(B - C)
}

// ICLARKE 3F
//=========================================================================
/**
 * @brief Calculates the inverse Clarke transformation for three-phase signals.
 *
 * @param v Pointer to the inverse Clarke transformation structure.
 *
 * @note This function computes the inverse Clarke transformation for three-phase signals.
 */
void iclarke3F_calc(volatile iclarke3F_struct *v)
{
    v->a = v->D;                                           // A = Alfa
    v->b = ( -v->D + SQ3 * v->Q ) * 0.5F;                // B = -1/2*Alfa + sqrt(3)/2*Beta
}

// Rotation (clockwise)
//=========================================================================
/**
 * @brief Calculates the rotation transformation (clockwise).
 *
 * @param v Pointer to the rotation transformation structure.
 *
 * @note This function computes the rotation transformation (clockwise).
 */
void rot_calc(volatile rot_struct *v)
{
    v->d = v->D*v->cosFi + v->Q*v->sinFi;              // d = Alfa(D)*cos(Fi) + Beta(Q)*sin(Fi)
    v->q = v->Q*v->cosFi - v->D*v->sinFi ;             // q = -Alfa(D)*sin(Fi) + Beta(Q)*cos(Fi)
}

// Inverse rotation (counterclockwise)
//=========================================================================
/**
 * @brief Calculates the inverse rotation transformation (counterclockwise).
 *
 * @param v Pointer to the inverse rotation transformation structure.
 *
 * @note This function computes the inverse rotation transformation (counterclockwise).
 */
void irot_calc(volatile irot_struct *v)
{
    v->alpha = v->d*v->cosFi - v->q*v->sinFi;              // Alfa(D) = d*cos(Fi) - q*sin(Fi)
    v->beta = v->d*v->sinFi + v->q*v->cosFi;              // Beta(Q) = d*sin(Fi) + q*cos(Fi)
}

// Angle generation
//=========================================================================
/**
 * @brief Generates the angle.
 *
 * @param v Pointer to the angle generation structure.
 *
 * @note This function generates the angle.
 */
void angle_calc(volatile angle_struct *v)
{
    // Integrator
    v->angle += v->freq*v->Ts*2;
    v->angle = (v->angle > 1) ? (v->angle - 2) : v->angle;
}

// SVPWM
//=========================================================================
/**
 * @brief Calculates the Space Vector Pulse Width Modulation (SVPWM).
 *
 * @param v Pointer to the SVPWM structure.
 *
 * @note This function calculates the Space Vector Pulse Width Modulation (SVPWM).
 */
void svpwm_calc(volatile svpwm_struct *v)
{
    /* Input is saturated between ±1/sqrt(3) = ±0.577 to ensure the result lies between ±0.5.
       Maximum simple line-to-line voltages achievable with a bus value of 1 lie between ±0.5.
       SVPWM reduces line voltages by approximately 15.4% by adding the homopolar component.
       The homopolar component is not visible in line-line voltages, effectively synthesizing something slightly larger than ±0.5.
       Desired ±1/sqrt(3) is approximately 15.4% larger.
       Duties (Da, Db, and Dc) range from 0 to 1. */

    // Auxiliary variables for SVPWM
    float Va, Vb, Vc, max, min, h;

    // Calculate Va, Vb, and Vc for three-phase system without neutral
    Va = v->alpha;                                      // A = Alfa
    //Vb = (- v->valfa + SQ3*v->vbeta)*0.5;              // B = -1/2*Alfa + sqrt(3)/2*Beta
    Vb = (- v->alpha + SQ3*v->beta)*DIV2;              // B = -1/2*Alfa + sqrt(3)/2*Beta
    Vc = - Va - Vb;                                     // C = - A - B

    // Homopolar addition
    // Select maximum
    max = Va;
    max = (Vb >= max) ? Vb : max;
    max = (Vc >= max) ? Vc : max;
    // Select minimum
    min = Va;
    min = (Vb <= min) ? Vb : min;
    min = (Vc <= min) ? Vc : min;
    // Calculate homopolar component
    h = (max + min)*DIV2;

    // Generate duty cycles (range from 0 to 1)
    // Convert sinusoids ranging up to 0.5 to sinusoids ranging from 0 to 1
    v->Da = (Va - h + 0.5F);
    v->Db = (Vb - h + 0.5F);
    v->Dc = (Vc - h + 0.5F);
}

// RAMP
//=========================================================================
/**
 * @brief Calculates the ramp.
 *
 * @param v Pointer to the ramp structure.
 *
 * @note This function calculates the ramp.
 */
void rampa_calc(volatile rampa_struct *v)
{
    if (v->enable)
    {
        if(v->out < v->in)
        {
            v->out += v->Incr;
            if(v->out > v->in)
                v->out = v->in;
            else;
        }
        else if(v->out > v->in)
        {
            v->out -= v->Incr;
            if(v->out < v->in)
                v->out = v->in;
            else;
        }
        else;
    }
    else
    {
        v->out = 0.0F;
    }
}

/**
 * @brief Calculates the dual ramp.
 *
 * @param v Pointer to the dual ramp structure.
 *
 * @note This function calculates the dual ramp.
 */
void rampa_dual_calc(volatile rampa_dual_struct *v)
{
    if (v->enable)
    {
        if(v->out < v->in)
        {
            v->out += v->Incr;
            if(v->out > v->in)
                v->out = v->in;
            else;
        }
        else if(v->out > v->in)
        {
            v->out -= v->Decr;
            if(v->out < v->in)
                v->out = v->in;
            else;
        }
        else;
    }
    else
    {
        v->out = 0;
    }
}

// DATALOG
//=========================================================================
/**
 * @brief Calculates the data log.
 *
 * @param dl Pointer to the data log structure.
 *
 * @note This function calculates the data log.
 */
void datalog_calc(volatile datalog_struct *dl)
{
    if(dl->estat)
    {
        if(dl->estat == 1)
        {
            dl->i = 0;
            dl->j = 0;
            dl->estat++;
        }

        if(dl->i < N_DATALOG)    // While not all values are stored
        {
            if((++dl->j) == dl->prescaler)    // If it's time to store
            {
                dl->log[dl->i++] = *(dl->var);    // Store
                dl->j = 0;
            }
        }
        else
            dl->estat = 0;        // Enter once more to set state to 3
    }
}

// First-order filter
//=========================================================================
/**
 * @brief Initializes the first-order filter.
 *
 * @param v Pointer to the first-order filter structure.
 *
 * @note This function initializes the first-order filter.
 */
void filtreLP_init(volatile filtreLP_struct *v)
{
    float aux;
    aux = v->fc* v->Ts;                                  // fc*Ts (fc in kHz)
    aux = aux * 1000.0;                                  // Convert kHz to Hz
    aux = PI2 * aux;                                      // 2*pi*fc*Ts
    v->alfa = aux/(aux + 1.0);                            // 2*pi*fc*Ts/(2*pi*fc*Ts + 1)
}

/**
 * @brief Calculates the first-order filter.
 *
 * @param v Pointer to the first-order filter structure.
 *
 * @note This function calculates the first-order filter.
 */
void filtreLP_calc(volatile filtreLP_struct *v)
{
    if (v->enable)
    {
        v->out = (v->alfa * (v->in - v->out)) + v->out;    // Filter out(k) = alfa*in(k) + (1-alfa)*out(k-1)
    }
    else
    {
        v->out = v->in;        // Without filter. Out(k) = In(k)
    }
}

// AVERAGE
//=========================================================================
/**
 * @brief Calculates the average of 10 samples.
 *
 * @param v Pointer to the structure containing the samples.
 *
 * @note This function calculates the average of 10 samples.
 */
void avg_calc_10_samples (volatile avg_struct_10 *v){

    v->out = (v->in[0] + v->in[1] + v->in[2] + v->in[3] + v->in[4] + v->in[5] + v->in[6] + v->in[7] + v->in[8] + v->in[9]) * 0.1F;

    // Copy previous values
    v->in[9] = v->in[8];
    v->in[8] = v->in[7];
    v->in[7] = v->in[6];
    v->in[6] = v->in[5];
    v->in[5] = v->in[4];
    v->in[4] = v->in[3];
    v->in[3] = v->in[2];
    v->in[2] = v->in[1];
    v->in[1] = v->in[0];
}

// RMS CALC
//=========================================================================
/**
 * @brief Calculates the Root Mean Square (RMS).
 *
 * @param v Pointer to the RMS structure.
 *
 * @note This function calculates the Root Mean Square (RMS).
 */
void RMS_calc(volatile RMS_struct *v){
    // Calculate RMS output current.
    //-----------------------------------------------------------------------------------------
    v->Sq_Sum += (float) (v->Measure * v->Measure)* v->T_exec;
    // Execute calculation at the zero crossing of the angle
    //
    if (v->Freq > 0.0F) {
        if (v->Angle_ant < 0.0F && v->Angle >= 0.0F) {
           // Calculate RMS
            v->Out_RMS = sqrtf((float) v->Sq_Sum * v->Freq);
            v->Sq_Sum = 0;
        }
        else;
    }
    else if (v->Freq < 0.0F){
        if (v->Angle_ant > 0.0F && v->Angle <= 0.0F) {
            // Calculate RMS
            v->Out_RMS = sqrtf((float) v->Sq_Sum * v->Freq * (-1.0F));
            v->Sq_Sum = 0;
        }
        else;
        //do nothing
    }
    else;
    v->Angle_ant = v->Angle;
}

// Step
//=========================================================================
/**
 * @brief Calculates the step function.
 *
 * @param v Pointer to the step structure.
 *
 * @note This function calculates the step function.
 */
void step_calc(volatile step_struct *v)
{
    // Calculate step width in pulses to count
    v->Pulses = (uint32_t)((v->fs) * (v->t_step));

    // If enabled, perform the step and start counting
    if (v->enable == 1 && v->Counter < v->Pulses){
        v->Out = v->In + v->Step;
        v->Counter++;
    }
    // When reaching the time limit, remove step and reset the counter
    else if (v->enable == 1 && v->Counter >= v->Pulses){
        v->Out = v->In;
        v->Counter = 0;
        v->enable = 0;
    }
    // If not enabled
    else v->Out = v->In;
}
