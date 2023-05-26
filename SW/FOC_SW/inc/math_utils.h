#ifndef MATHUTILS_LIB_H
#define MATHUTILS_LIB_H

// Macro to determine the sign of a value
#define _sign(a) (((a) < 0) ? -1 : ((a) > 0))

// Macro to round a floating-point number to the nearest integer
#define _round(x) (((x) >= 0) ? (long)((x) + 0.5f) : (long)((x) - 0.5f))

// Macro to calculate the absolute value of a number
#define _abs(x) ((x) < 0 ? -(x) : (x))

// Macro to constrain a value within a specified range
#define _constrain(amt, low, high) (((amt) < (low)) ? (low) : (((amt) > (high)) ? (high) : (amt)))

// Macro to calculate the square root of a number
#define _sqrt(a) (_sqrtApprox(a))



// Utility defines
#define _2_SQRT3 1.15470053838f
#define _SQRT3 1.73205080757f
#define _1_SQRT3 0.57735026919f
#define _SQRT3_2 0.86602540378f
#define _SQRT2 1.41421356237f
#define _120_D2R 2.09439510239f
#define _PI 3.14159265359f
#define _PI_2 1.57079632679f
#define _PI_3 1.0471975512f
#define _2PI 6.28318530718f
#define _3PI_2 4.71238898038f
#define _PI_6 0.52359877559f
#define _RPM_TO_RADS 0.10471975512f

// Function prototypes
float _sin(float a);
float _cos(float a);
float _normalizeAngle(float angle);
float _electricalAngle(float shaft_angle, int pole_pairs);
float _sqrtApprox(float number);
void _clarkeTransform(float a, float b, float *alpha, float *beta);
void _parkTransform(float alpha, float beta, float theta, float *d, float *q);
void _inverseParkTransform(float d, float q, float theta, float *alpha, float *beta);

#endif  // MATHUTILS_LIB_H
