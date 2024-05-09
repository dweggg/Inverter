#include "CONTROL.h"
#include <math.h>
#include "main.h"
/**
 * @file control.c
 * @brief Source file for control logic.
 */

/**
 * @brief Control function.
 *
 * This function implements the control logic based on measurements.
 * For now, it sets a constant duty cycle.
 *
 * @param measurements Measurements structure.
 * @param duties Pointer to the duties structure.
 */
void calc_duties(float vd, float vq, float vDC, float freq, volatile Duties *duties) {
	static angle_struct angle;
	angle.freq = freq;
	angle.Ts = TS;
	angle_calc(&angle);

	static irot_struct irot;
	irot.d = vd/vDC;
	irot.q = vq/vDC;
	irot.sinFi = sin(angle.angle*M_TWOPI);
	irot.cosFi = cos(angle.angle*M_TWOPI);
    irot_calc(&irot);

    static svpwm_struct svpwm;
    // Assign values to SVPWM structure
    svpwm.alpha = irot.alpha;
    svpwm.beta = irot.beta;
    svpwm_calc(&svpwm);

    // Assign SVPWM duties
    duties->Da = svpwm.Da;
    duties->Db = svpwm.Db;
    duties->Dc = svpwm.Dc;

}
