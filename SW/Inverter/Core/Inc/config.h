#ifndef CONFIG_H
#define CONFIG_H

// General parameters
#define fsw 50000.0F // [Hz] Switching frequency

// Motor Parameters
#define PP 3.0F		// [ad] Number of pole pairs (n/2)
#define Rs 0.1F      // [Ohm] Phase resistance
#define Ld 0.001F    // [H] d-axis inductance
#define Lq 0.001F    // [H] q-axis inductance
#define lambda 0.001F // [V,pk*s/rad] Permanent magnet flux linkage
#define is_max 100.0F // [A,pk] Maximum phase current
#define Tem_max 27.0F // [N*m] Maximum electromechanical torque
#define wm_max 20000.0F // [rpm] Maximum mechanical speed

// Control parameters
#define KFW 0.85F

#define currentLoopMp 0.15F;
#define currentLoopTime 0.0004F;

#define speedLoopMp 0.15F;
#define speedLoopTime 0.0004F;

#define voltageLoopMp 0.15F;
#define voltageLoopTime 0.0004F;



// Thermal limits
#define Tmax_motor 100.0F // [degC] Maximum motor temperature -> deratingFactor = 0.0
#define Tmax_inv 80.0F // [degC] Maximum inverter temperature -> deratingFactor = 0.0

#define Tderating_motor 80.0F // [degC] Motor temperature from which derating is applied -> deratingFactor = 1.0
#define Tderating_inv 60.0F // [degC] Inverter temperature from which derating is applied -> deratingFactor = 1.0

// Electrical limits
#define VDC_max 600.0F // [V] Maximum DC voltage
#define iPhase_max 120.0F // [A] Maximum instantaneous phase current
#define we_max	1200.0F	// [Hz] Maximum frequency that can be generated
#define deadtime	100.0e-9F	// [s] Dead time

// Macros
#define sign(x) ((x >= 0) ? 1 : -1)
#define vabs(x) (x = (x >= 0) ? x: -x)


// Function prototype for variable initialization
void initVariables();


// Global variable declarations

extern volatile float Ts;
extern volatile float isc;
#endif /* CONFIG_H */
