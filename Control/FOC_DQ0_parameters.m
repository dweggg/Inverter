clc, clear

%% Permanent magnet synchronous machine constant parameters
%{
motor = struct();
motor.n = 8;                                 % [ad] Number of poles 
motor.kE = 49.7e-3*60/(2*pi);                % [Vrmsphn/krpm(wm)] Speed constant 
motor.lambda = motor.kE / (sqrt(3) * (motor.n/2));  % [Wb] PM flux linkage
motor.Ld =  0.520e-3;                        % [H] d-axis inductance
motor.Lq =  1.265e-3;                        % [H] q-axis inductance
motor.epsilon = motor.Lq/motor.Ld;           % [ad] Saliency ratio
motor.Rs = 0.135;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
motor.maxRPM = 7000;                         % [rpm] Motor maximum angular speed
motor.K_FW = 0.85;                           % [%] Field Weakening safety factor
motor.Te_max = 130;                          % [N·m] Motor maximum angular torque
motor.I_max = 180;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
%}


motor = struct();
motor.n = 6;                                 % [ad] Number of poles 
motor.lambda = 0.054758;                     % [Wb] PM flux linkage
motor.Ld =  0.2450e-3;                       % [H] d-axis inductance
motor.Lq =  0.3674e-3;                       % [H] q-axis inductance
motor.epsilon = motor.Lq/motor.Ld;           % [ad] Saliency ratio
motor.Rs = 0.15;                             % [Ohm]     Stator phase resistance (phase-to-phase/2)
motor.maxRPM = 20000;                        % [rpm] Motor maximum angular speed
motor.K_FW = 0.80;                           % [%] Field Weakening safety factor
motor.Te_max = 26;                           % [N·m] Motor maximum angular torque
motor.I_max = 103;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
%}

%% Battery parameters
battery = struct();
battery.ns = 140;
battery.np = 5;
battery.SoC_init = 0.9;
battery.SoC = [0 35 40 50 65 85 100];                  % [%] Battery SOC LUT
battery.OCV = [2.5 3 3.2 3.6 3.8 4.0 4.2].*battery.ns; % [V] Battery voltage LUT
battery.Q = 2.5*battery.np;                            % [A·h] Battery capacity
battery.R0 = 0.0012;                                   % [V] Battery internal resistance
battery.R1 = 0.0004;                                   % [V] Battery polarization resistance
battery.C1 = 4074;                                     % [V] Battery polarization capacitance                                    

%% Inverter parameters
inv = struct();
inv.FW = struct();

inv.fsw = 8e3;
inv.Tsw = 1/inv.fsw;

inv.Ts_PI = 5e-4;

inv.tr_id = inv.Ts_PI*2;                   % Rise time [s]
inv.alpha_id = log(9)/inv.tr_id;
inv.Kp_id = inv.alpha_id*motor.Ld;
inv.Ki_id = inv.alpha_id*motor.Rs;
inv.Kaw_id = 1/inv.Ki_id;

inv.tr_iq = inv.Ts_PI*2;                   % Rise time [s]
inv.alpha_iq = log(9)/inv.tr_iq;
inv.Kp_iq = inv.alpha_iq*motor.Lq;
inv.Ki_iq = inv.alpha_iq*motor.Rs;
inv.Kaw_iq = 1/inv.Ki_iq;

inv.FW.KFW = 0.8;                % Relationship between the maximum available voltage and the applicable voltage [pu]
inv.FW.tsV = 200e-3;              % Flux.weakening closed-loop settling time (s)
inv.FW.Is_WP = motor.I_max;               % Current magnitude working point (A)
inv.FW.gamma_WP = 3*pi/4;     % Current angle working point (rad)

inv.FW.A = -motor.Rs * inv.FW.Is_WP * sin(inv.FW.gamma_WP) * (inv.FW.Is_WP * cos(inv.FW.gamma_WP) * (motor.Ld-motor.Lq) + motor.lambda) / (motor.Lq^2 * inv.FW.Is_WP^2 * sin(inv.FW.gamma_WP)^2 + (motor.Ld * inv.FW.Is_WP * cos(inv.FW.gamma_WP) + motor.lambda)^2);
inv.FW.B = motor.Rs^2 * inv.FW.Is_WP^2 * sin(inv.FW.gamma_WP)^2 * (inv.FW.Is_WP * cos(inv.FW.gamma_WP) * (motor.Ld-motor.Lq) + motor.lambda)^2 / ((motor.Lq^2 * inv.FW.Is_WP^2 * sin(inv.FW.gamma_WP)^2 + (motor.Ld * inv.FW.Is_WP * cos(inv.FW.gamma_WP) + motor.lambda)^2))^2;
inv.FW.C = ((motor.Lq^2 * inv.FW.Is_WP^2 * sin(inv.FW.gamma_WP)^2 + (motor.Ld * inv.FW.Is_WP * cos(inv.FW.gamma_WP) + motor.lambda)^2)) * (motor.Rs^2 * inv.FW.Is_WP^2 - (battery.OCV(end)/sqrt(3))^2) / ((motor.Lq^2 * inv.FW.Is_WP^2 * sin(inv.FW.gamma_WP)^2 + (motor.Ld * inv.FW.Is_WP * cos(inv.FW.gamma_WP) + motor.lambda)^2))^2;


inv.FW.we_WP = inv.FW.A + sqrt(inv.FW.B-inv.FW.C); 

inv.FW.A = 2*inv.FW.Is_WP*(motor.Rs*inv.FW.we_WP*inv.FW.tsV*inv.FW.Is_WP*(motor.Ld-motor.Lq)*cos(inv.FW.gamma_WP)^2);
inv.FW.B = inv.FW.Is_WP*cos(inv.FW.gamma_WP)*(5*(motor.Ld-motor.Lq)*(motor.Rs-inv.FW.tsV*(motor.Ld+motor.Lq)*inv.FW.we_WP^2/5)*inv.FW.Is_WP*sin(inv.FW.gamma_WP) + motor.lambda*inv.FW.we_WP*(motor.Rs*inv.FW.tsV - 5*motor.Lq));
inv.FW.C = inv.FW.Is_WP*inv.FW.we_WP*(sin(inv.FW.gamma_WP)*motor.Ld*inv.FW.we_WP*inv.FW.tsV*motor.lambda + inv.FW.Is_WP*(motor.Rs*(motor.Ld-motor.Lq)*inv.FW.tsV+5*motor.Ld*motor.Lq));

inv.FW.Kp_V_Delta = 0;
inv.FW.Ki_V_Delta = -5*(battery.OCV(end)/sqrt(3))/(inv.FW.A + inv.FW.B - inv.FW.C);

%inv.FW.K0_V_Delta = inv.FW.Kp_V_Delta + inv.FW.Ki_V_Delta*inv.Ts_PI/2;
%inv.FW.K1_V_Delta = -inv.FW.Kp_V_Delta + inv.FW.Ki_V_Delta*inv.Ts_PI/2;


%% Car parameters
car = struct();
% car.GR = 4;                                         % [ad] Gear ratio
 car.GR = 11.2;                                      % [ad] Gear ratio
car.Mass = 300;                                     % [kg] Car mass
car.Rw = 0.220;                                     % [m] Wheel radius
car.Af = 1.1;                                       % [m^2] Frontal area
car.Cd = 1.5;                                       % [ad] Drag coefficient
car.RR = 0.017;                                     % [ad] Rolling resistance coefficient
car.T_Te = 0.2;                                     % [s] Time from Te = 0 to Te = Te_max
car.motor_number = 1;                               % [ad] Number of motors in the car
