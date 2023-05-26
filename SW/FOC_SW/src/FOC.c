#include "math_utils.h"

#define MAX_ITERATIONS 10
#define TOLERANCE 1e-2

float iq_ref_MTPA(float Ld, float Lq, float lambda, float n, float Te_ref);



float iq_ref_MTPA(float Te_ref, float Ld, float Lq, float lambda, float n) {
    float iq_ref_MTPA = 0.0;
    float iq_prev = 0.0;
    float f, df, delta_iq;

    // Perform Newton-Raphson iterations
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Calculate the function value and its derivative at iq

        // Iq_ref from torque, MTPA. Extracted from
        // https://iris.unipa.it/retrieve/handle/10447/406125/862725/document.pdf,
        // eqn 9
        f = iq_ref_MTPA * iq_ref_MTPA * iq_ref_MTPA * iq_ref_MTPA +
            iq_ref_MTPA * Te_ref * lambda / ((3.0/2.0) * (n/2.0) * (Ld - Lq) * (Ld - Lq)) -
            Te_ref * Te_ref / (((3.0/2.0) * (n/2.0) * (Ld - Lq)) * ((3.0/2.0) * (n/2.0) * (Ld - Lq)));
        df = 4.0 * iq_ref_MTPA * iq_ref_MTPA * iq_ref_MTPA +
             Te_ref * lambda / ((3.0/2.0) * (n/2.0) * (Ld - Lq) * (Ld - Lq));

        // Calculate the update for iq
        delta_iq = f / df;

        // Update iq
        iq_prev = iq_ref_MTPA;
        iq_ref_MTPA -= delta_iq;

        // Check convergence
        if (_abs(delta_iq) < TOLERANCE) {
            break;
        }
    }

    return iq_ref_MTPA;
}
