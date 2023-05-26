clc, clear

%% Permanent magnet synchronous machine constant parameters
motor = struct();

motor.Ke = 0.1;                                     % [V/(rad/s)] Speed constant
motor.n = 6;                                        % [ad] Number of poles 
motor.lambda = sqrt (2/3) * motor.Ke / (motor.n/2); % [Wb] PM flux linkage
motor.Ld = 0.2372e-3;                               % [H] d-axis inductance
motor.Lq = 0.4459e-3;                               % [H] q-axis inductance
motor.Rs = 0.0201;                                  % [Ohm] Stator phase resistance (phase-to-phase/2)
motor.J = 0.01;                                     % [N·m^2] Rotor moment of inertia
motor.B = 0.005;                                    % [ad] Rotor viscous friction coefficient
motor.maxRPM = 20000;                               % [rpm] Motor maximum angular speed
motor.nomRPM = 12500;                               % [rpm] Motor maximum angular speed
motor.I_max = 200;                                  % [A] Motor maximum output current


%% Battery parameters
battery = struct();
battery.V = 580;                                    % [V] Battery voltage
