clc, clear

%% Permanent magnet synchronous machine constant parameters
motor = struct();

motor.lambda = 0.10642288;                    % [Wb] PM flux linkage
motor.Ld = 0.52e-3;                           % [H] d-axis inductance
motor.Lq = 1.26e-3;                           % [H] q-axis inductance
motor.Rs = 115e-3;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
motor.n = 8;                                  % [ad] Number of poles 
motor.J = 0.01;                               % [N·m^2] Rotor moment of inertia
motor.B = 0.005;                              % [ad] Rotor viscous friction coefficient
motor.maxRPM = 20000;                         % [rpm] Motor maximum angular speed