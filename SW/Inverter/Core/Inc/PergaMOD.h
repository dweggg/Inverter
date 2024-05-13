/*
 * @file PergaMOD.h
 * @brief Library consolidating all the hardware-independent libraries of CITCEA.
 * This library is based on Alexandria created by Gabriel Gross and Quim Lopez Mestre in September 2006.
 * Created by Gabriel Gross, Daniel Heredero, and Tomas Lledo in December 2015.
 * Translated to floats by Lucas Bouzon in March 2020.
 */

/*
                       ____                      __  __  ___  ____   _
                      |  _ \ ___ _ __ __ _  __ _|  \/  |/ _ \|  _ \ | |__
                      | |_) / _ \ '__/ _` |/ _` | |\/| | | | | | | || '_ \
                      |  __/  __/ | | (_| | (_| | |  | | |_| | |_| || | | |
                      |_|   \___|_|  \__, |\__,_|_|  |_|\___/|____(_)_| |_|
                                     |___/

*/

#ifndef __PERGAMON_FLOAT_H__
#define __PERGAMON_FLOAT_H__


#include "stdint.h"

/** @defgroup Math_Constants Math Constants
 *  @{
 */
#define SQ2		1.4142135624F	/**< Square root of 2 */
#define ISQ2	0.7071067812F	/**< Inverse of square root of 2 */
#define SQ3		1.7320508076F	/**< Square root of 3 */
#define ISQ3	0.5773502692F	/**< Inverse of square root of 3 */
#define PI 		3.1415926536F	/**< Pi */
#define IPI 	0.3183098862F	/**< Inverse of Pi */
#define PI2 	6.2831853072F	/**< 2*Pi */
#define IPI2 	0.1591549431F	/**< Inverse of (2*Pi) */
#define INV_DEG 0.0027777778F	/**< Inverse of 360 */
#define INV3	0.3333333333F	/**< Inverse of 3 */
#define DIV2	0.5F			/**< 1/2 */
/** @} */

/**
 * @defgroup Proportional - Integral Controllers
 * @{
 */

/**
 * @brief PI Controller with internal saturation, anti-windup, and feedforward.
 */
typedef struct
{
	uint16_t		enable;			/**< Enable flag for the controller */
	float			Ts;				/**< Execution period */
	float			Kp;				/**< Proportional gain */
	float			Ki;				/**< Integral gain */
	float			Kaw;			/**< Anti-windup gain */
	float			e[2];			/**< Error at current and previous step */
	float			pi_consig;		/**< Setpoint */
	float			pi_fdb;	 		/**< Feedback */
	float			pi_out_max;		/**< Maximum output */
	float			pi_out_min;		/**< Minimum output */
	float           pi_out_presat;	/**< Output before saturation */
	float           pi_out_postsat;	/**< Output after saturation */
	float			pi_out;	 		/**< Controller output */
	float			pi_int[2];    	/**< Integrator Part */
	float			pi_ffw[2];  	/**< Feedforward at current and previous step */
	void(*calc)();					/**< Pointer to the calculation function */
} pi_aw_struct;

/**
 * @brief Initializes the PI controller with anti-windup.
 * @param v Pointer to the PI controller structure.
 */
void pi_aw_calc(volatile pi_aw_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief PI Controller with external saturation and feedforward.
 */
typedef struct
{
	uint16_t		enable;			/**< Enable flag for the controller */
	float			Ts;				/**< Execution period */
	float			Kp;				/**< Proportional gain */
	float			Ki;				/**< Integral gain */
	float			K0;				/**< K0 = Kp + (Ts*Ki)/2 */
	float			K1;				/**< K0 = -Kp + (Ts*Ki)/2 */
	float			e[2];			/**< Error at current and previous step */
	float			pi_consig;		/**< Setpoint */
	float			pi_fdb;	 		/**< Feedback */
	float			pi_out_max;		/**< Maximum output */
	float			pi_out_min;		/**< Minimum output */
	float			pi_out;	 		/**< Controller output */
	float			pi_ffw[2];  	/**< Feedforward at current and previous step */
	void(*init)();					/**< Pointer to the initialization function */
	void(*calc)();					/**< Pointer to the calculation function */
} pi_struct;

/**
 * @brief Initializes the PI controller.
 * @param v Pointer to the PI controller structure.
 */
void pi_init(volatile pi_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Calculates the output of the PI controller.
 * @param v Pointer to the PI controller structure.
 */
void pi_calc(volatile pi_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Calculates the output of the PI controller with external saturation.
 * @param v Pointer to the PI controller structure.
 */
void pi_extsat_calc(volatile pi_struct *v);

/** @} */

/**
 * @defgroup Transformation_Functions Clarke and Park Transformations
 * @{
 */

/**
 * @brief Clarke transformation for three-phase systems.
 */
typedef struct
{
	float			a;			/**< Phase A input */
	float			b;			/**< Phase B input */
	float			D;			/**< D-axis output */
	float			Q;			/**< Q-axis output */
	void(*calc)();				/**< Pointer to the calculation function */
} clarke3F_struct;

/**
 * @brief Calculates the Clarke transformation.
 * @param v Pointer to the Clarke transformation structure.
 */
void clarke3F_calc(volatile clarke3F_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Inverse Clarke transformation for three-phase systems.
 */
typedef struct
{
	float			D;			/**< D-axis input */
	float			Q;			/**< Q-axis input */
	float			a;			/**< Phase A output */
	float			b;			/**< Phase B output */
	void(*calc)();				/**< Pointer to the calculation function */
} iclarke3F_struct;

/**
 * @brief Calculates the inverse Clarke transformation.
 * @param v Pointer to the inverse Clarke transformation structure.
 */
void iclarke3F_calc(volatile iclarke3F_struct *v);

/**
 * @brief Rotates the DQ axis in the opposite direction (clockwise).
 */
typedef struct
{
	float			D;			/**< D-axis input */
	float			Q;			/**< Q-axis input */
	float			sinFi;		/**< Sine of the angle of rotation */
	float			cosFi;		/**< Cosine of the angle of rotation */
	float			d;			/**< Rotated D-axis */
	float			q;			/**< Rotated Q-axis */
	void(*calc)();				/**< Pointer to the calculation function */
} rot_struct;

/**
 * @brief Calculates the rotation in the opposite direction.
 * @param v Pointer to the rotation structure.
 */
void rot_calc(volatile rot_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Inverse rotation (counterclockwise).
 */
typedef struct
{
	float			d;			/**< D-axis input */
	float			q;			/**< Q-axis input */
	float			sinFi;		/**< Sine of the angle of rotation */
	float			cosFi;		/**< Cosine of the angle of rotation */
	float			alpha;		/**< alpha output */
	float			beta;		/**< beta output */
	void(*calc)();				/**< Pointer to the calculation function */
} irot_struct;

/**
 * @brief Calculates the inverse rotation.
 * @param v Pointer to the inverse rotation structure.
 */
void irot_calc(volatile irot_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/** @} */

/**
 * @defgroup Utility_Functions Utility Functions
 * @{
 */

/**
 * @brief Generates an angle based on a fixed frequency.
 */
typedef struct {
	float 		freq;			/**< Frequency of the network */
	float 		Ts;				/**< Execution frequency of the angle integration */
	float 		angle;			/**< Network angle */
	void(*calc)();					/**< Pointer to the calculation function */
} angle_struct;

/**
 * @brief Calculates the angle generation.
 * @param p Pointer to the angle structure.
 */
void angle_calc(volatile angle_struct *p) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Space Vector Pulse Width Modulation (SVPWM) implementation.
 */
typedef struct
{
	float			alpha; 		/**< Input in per-unit for alpha phase (0deg)*/
	float			beta;		/**< Input in per-unit for beta phase (90deg)*/
	float			Da;			/**< Output for phase A (0-1) */
	float			Db;			/**< Output for phase B (0-1) */
	float			Dc;			/**< Output for phase C (0-1) */
	void(*calc)();				/**< Pointer to the calculation function */
} svpwm_struct;

/**
 * @brief Calculates the SVPWM outputs.
 * @param v Pointer to the SVPWM structure.
 */
void svpwm_calc(volatile svpwm_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/** @} */
/**
 * @defgroup Signal_Processing_Functions Signal Processing Functions
 * @{
 */

/**
 * @brief Single-ramp generator.
 */
typedef struct
{
	float 		in;				/**< Input signal */
	float 		out;			/**< Output signal */
	float 		Incr;			/**< Increment */
	uint8_t 	enable;			/**< Enable flag */
	void(*calc)();				/**< Pointer to the calculation function */
} rampa_struct;

/**
 * @brief Dual-ramp generator.
 */
typedef struct
{
	float 		in;				/**< Input signal */
	float 		out;			/**< Output signal */
	float 		Incr;			/**< Increment */
	float 		Decr;			/**< Decrement */
	uint8_t 	enable;			/**< Enable flag */
	void(*calc)();				/**< Pointer to the calculation function */
} rampa_dual_struct;

/**
 * @brief Calculates the output of the single ramp generator.
 * @param v Pointer to the single ramp generator structure.
 */
void rampa_calc(volatile rampa_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Calculates the output of the dual ramp generator.
 * @param v Pointer to the dual ramp generator structure.
 */
void rampa_dual_calc(volatile rampa_dual_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief Data logger for logging variables.
 */

#define N_DATALOG 256	/**< Number of samples for the data log */

typedef struct
{
	uint16_t		i;				/**< State variable */
	uint16_t		j;				/**< State variable */
	uint16_t		estat;			/**< State: 0=stopped, 1=init, 2=running */
	uint16_t		prescaler;		/**< Prescaler */
	float			*var;			/**< Pointer to variables */
	void(*calc)();					/**< Pointer to the calculation function */
	float	    	log[N_DATALOG];	/**< Log array */
} datalog_struct;

/**
 * @brief Calculates the data log.
 * @param dl Pointer to the data log structure.
 */
void datalog_calc(volatile datalog_struct *dl);

/**
 * @brief Moving average filter for 10 samples.
 */
typedef struct
{
    float       out;        /**< Output variable */
    float       in[10];     /**< Input and past samples */
}avg_struct_10;

/**
 * @brief Calculates the moving average for 10 samples.
 * @param v Pointer to the moving average structure.
 */
void avg_calc_10_samples(volatile avg_struct_10 *v);

/**
 * @brief Root Mean Square (RMS) calculation.
 */
typedef struct {
    float   	T_exec;     		/**< Execution frequency of the function */
    float     	Measure;    		/**< Signal to be RMSed */
    float   	Sq_Sum;     		/**< Sum of squares */
    float     	Out_RMS;    		/**< RMSed signal */
    float     	Freq;       		/**< Output frequency of the PLL */
    float     	Angle;      		/**< Angle */
    float     	Angle_ant;  		/**< Previous angle */
} RMS_struct;

/**
 * @brief Calculates the RMS.
 * @param v Pointer to the RMS structure.
 */
void RMS_calc(volatile RMS_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/**
 * @brief First-order low-pass filter.
 */
typedef struct
{
	float 		in;				/**< Input signal */
	float 		out;			/**< Output signal */
	float 		alfa;			/**< Filter coefficient */
	float		Ts;				/**< Execution period */
	float		fc;				/**< Cutoff frequency */
	uint16_t 	enable;			/**< Enable flag */
	void(*init)();				/**< Pointer to the initialization function */
	void(*calc)();				/**< Pointer to the calculation function */
} filtreLP_struct;

/**
 * @brief Initializes the first-order low-pass filter.
 * @param v Pointer to the filter structure.
 */
void filtreLP_init(volatile filtreLP_struct *v);

/**
 * @brief Calculates the output of the first-order low-pass filter.
 * @param v Pointer to the filter structure.
 */
void filtreLP_calc(volatile filtreLP_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/** @} */

/**
 * @defgroup Miscellaneous_Functions Miscellaneous Functions
 * @{
 */

/**
 * @brief Step function generator.
 */
typedef struct
{
    float             fs;         /**< Function execution frequency */
    float             In;         /**< Input variable */
    float             Out;        /**< Output variable (with step when needed) */
    float             Step;       /**< Step amplitude */
    float             t_step;     /**< Step duration in seconds */
    uint32_t          Pulses;     /**< Pulse counter for seconds */
    uint32_t          Counter;    /**< Counter for pulses */
    uint16_t          enable;     /**< Enable flag */
	void(*calc)();                 /**< Pointer to the calculation function */
} step_struct;

/**
 * @brief Calculates the output of the step function generator.
 * @param v Pointer to the step generator structure.
 */
void step_calc(volatile step_struct *v) __attribute__( ( section ( ".ccmram" ) ) );

/** @} */

#endif // __PERGAMON_FLOAT_H__
