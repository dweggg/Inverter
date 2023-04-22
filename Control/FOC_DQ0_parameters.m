clc, clear

%% Permanent magnet synchronous machine constant parameters
motor = struct();

motor.lambda = 35e-3;                         % [Wb] PM flux linkage
motor.Ld = 0.2372e-3;                         % [H] d-axis inductance
motor.Lq = 0.4459e-3;                         % [H] q-axis inductance
motor.Rs = 0.0201;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
motor.n = 6;                                  % [ad] Number of poles 
motor.J = 0.01;                               % [N·m^2] Rotor moment of inertia
motor.B = 0.005;                              % [ad] Rotor viscous friction coefficient
motor.maxRPM = 25000;                         % [rpm] Motor maximum angular speed
motor.nomRPM = 12500;                         % [rpm] Motor maximum angular speed
motor.I_max = 150;                            % [A] Motor maximum output current
