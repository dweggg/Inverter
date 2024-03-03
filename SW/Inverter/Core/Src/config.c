#include "config.h"
#include "Pergamon_float.h"

// Initialize variables based on defined constants
void initVariables() {
    // General parameters
    volatile float Ts = 1.0F / fsw;

    // Motor parameters
    volatile float isc = lambda/Ld;

}
