clc, clear

%% Permanent magnet synchronous machine constant parameters
motor = struct();
motor.n = 10;                                % [ad] Number of poles 
motor.kE = 18.8;                             % [Vrmsphn/krpm(wm)] Speed constant 
motor.lambda = motor.kE*(60/(2*pi))/(1000*(motor.n/2));  % [Wb] PM flux linkage
motor.Ld =  0.12e-3;                         % [H] d-axis inductance
motor.Lq =  0.24e-3;                         % [H] q-axis inductance
motor.epsilon = motor.Lq/motor.Ld;           % [ad] Saliency ratio
motor.Rs = 0.135;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
motor.maxRPM = 20000;                        % [rpm] Motor maximum angular speed
motor.K_FW = 0.8;                            % [%] Field Weakening safety factor
motor.Te_max = 30;                           % [N·m] Motor maximum angular torque
motor.I_max = 105;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
        
%% Inverter parameters
inv = struct();

inv.tr_id = 10e-3;                   % Rise time [s]
inv.alpha_id = log(9)/inv.tr_id;
inv.Kp_id = inv.alpha_id*motor.Ld;
inv.Ki_id = inv.alpha_id*motor.Rs;

inv.tr_iq = 10e-3;                   % Rise time [s]
inv.alpha_iq = log(9)/inv.tr_iq;
inv.Kp_iq = inv.alpha_iq*motor.Lq;
inv.Ki_iq = inv.alpha_iq*motor.Rs;



%% Battery parameters
battery = struct();
battery.ns = 140;
battery.np = 5;
battery.SoC_init = 0.9;
battery.SoC = [0 35 40 50 65 85 100];                % [%] Battery SOC LUT
battery.OCV = [2.5 3 3.2 3.6 3.8 4.0 4.2].*battery.ns;% [V] Battery voltage LUT
battery.Q = 2.5*battery.np;                          % [A·h] Battery capacity
battery.R0 = 0.0012;                                 % [V] Battery internal resistance
battery.R1 = 0.0004;                                 % [V] Battery polarization resistance
battery.C1 = 4074;                                   % [V] Battery polarization capacitance                                    
%% Car parameters
car = struct();
car.GR = 11.2;                                        % [ad] Gear ratio
car.Mass = 250;                                     % [kg] Car mass
car.Rw = 0.228;                                     % [m] Wheel radius
car.Af = 1.1;                                       % [m^2] Frontal area
car.Cd = 1.5;                                       % [ad] Drag coefficient
car.RR = 0.017;                                     % [ad] Rolling resistance coefficient

car.motor_number = 4;                               % [ad] Number of motors in the car
