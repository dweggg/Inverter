#include "math_utils.h"

float SVPWM(float v_alpha, float v_beta, float Vdc) {
    // Set the voltage limits
    float weight = Vdc / (sqrt(3) * sqrt(v_alpha * v_alpha + v_beta * v_beta));
    float dlimit = _abs(v_alpha * weight); // Maximum limit for v_alpha
    float qlimit = _abs(v_beta * weight);  // Maximum limit for v_beta

    // Limit v_alpha within the bounds
    if (_abs(v_alpha) > dlimit) {
        v_alpha = (3 * _sign(v_alpha) * dlimit) / (2 * Vdc);
    } else {
        v_alpha = (3 * v_alpha) / (2 * Vdc);
    }

    // Limit v_beta within the bounds
    if (_abs(v_beta) > qlimit) {
        v_beta = (3 * _sign(v_beta) * qlimit) / (2 * Vdc);
    } else {
        v_beta = (3 * v_beta) / (2 * Vdc);
    }

    // Initialize duty cycle variables
    float duty_a = 0;
    float duty_b = 0;
    float duty_c = 0;

    // Sector calculations
    if ((v_alpha >= 0) && (v_beta >= 0)) {
        if (v_beta < sqrt(3) * v_alpha) {
            // Sector 0
            float t1 = 0.5 * (v_alpha - (v_beta / sqrt(3)));
            float t2 = v_beta / sqrt(3);
            float temp = 0.5 - t1 - t2;
            duty_a = 1 - temp;
            duty_b = 1 - (temp + 2 * t1);
            duty_c = temp;
        } else {
            // Sector 1
            float t1 = 0.5 * ((v_beta / sqrt(3)) - v_alpha);
            float t2 = 0.5 * ((v_beta / sqrt(3)) + v_alpha);
            float temp = 0.5 - t1 - t2;
            duty_b = 1 - temp;
            duty_a = 1 - (temp + 2 * t1);
            duty_c = temp;
        }
    }

    if ((v_alpha < 0) && (v_beta > 0)) {
        if (v_beta < (sqrt(3) * _abs(v_alpha))) {
            // Sector 2
            float t1 = v_beta / sqrt(3);
            float t2 = 0.5 * (_abs(v_alpha) - (v_beta / sqrt(3)));
            float temp = 0.5 - t1 - t2;
            duty_b = 1 - temp;
            duty_c = 1 - (temp + 2 * t1);
            duty_a = temp;
        } else {
            // Sector 1
            float t1 = 0.5 * ((v_beta / sqrt(3)) - v_alpha);
            float t2 = 0.5 * ((v_beta / sqrt(3)) + v_alpha);
            float temp = 0.5 - t1 - t2;
            duty_b = 1 - temp;
            duty_a = 1 - (temp + 2 * t1);
            duty_c = temp;
        }
    }

    if ((v_alpha < 0) && (v_beta <= 0)) {
        if (_abs(v_beta) <= sqrt(3) * _abs(v_alpha)) {
            // Sector 3
            float t1 = _abs(v_beta) / sqrt(3);
            float t2 = 0.5 * (_abs(v_alpha) - (_abs(v_beta) / sqrt(3)));
            float temp = 0.5 - t1 - t2;
            duty_c = 1 - temp;
            duty_b = 1 - (temp + 2 * t1);
            duty_a = temp;
        } else {
            // Sector 4
            float t1 = 0.5 * ((_abs(v_beta) / sqrt(3)) - v_alpha);
            float t2 = 0.5 * ((_abs(v_beta) / sqrt(3)) + v_alpha);
            float temp = 0.5 - t1 - t2;
            duty_c = 1 - temp;
            duty_a = 1 - (temp + 2 * t1);
            duty_b = temp;
        }
    }

    if ((v_alpha >= 0) && (v_beta < 0)) {
        if (_abs(v_beta) <= v_alpha * sqrt(3)) {
            // Sector 5
            float t1 = 0.5 * (v_alpha - (_abs(v_beta) / sqrt(3)));
            float t2 = _abs(v_beta) / sqrt(3);
            float temp = 0.5 - t1 - t2;
            duty_a = 1 - temp;
            duty_c = 1 - (temp + 2 * t1);
            duty_b = temp;
        } else {
            // Sector 4
            float t1 = 0.5 * ((_abs(v_beta) / sqrt(3)) - v_alpha);
            float t2 = 0.5 * ((_abs(v_beta) / sqrt(3)) + v_alpha);
            float temp = 0.5 - t1 - t2;
            duty_c = 1 - temp;
            duty_a = 1 - (temp + 2 * t1);
            duty_b = temp;
        }
    }

    return duty_a, duty_b, duty_c;
}
