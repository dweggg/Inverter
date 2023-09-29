% Clear workspace and command window
clc;
clear;

% Constants and motor specifications
P_max = 35e3;                       % Maximum Power (W)
Te_max = 26;                        % Maximum Electromagnetic Torque (Nm)
wm_max_rpm = 20e3;                  % Maximum Speed (RPM)
wm_max = wm_max_rpm * 2 * pi / 60;  % Maximum Speed (rad/s)

Vbat_min = 350;                     % Minimum Battery Voltage (V)
Vbat_max = 600;                     % Maximum Battery Voltage (V)
Vbat_nom = 540;                     % Nominal Battery Voltage (V)

Vs_min = Vbat_min / sqrt(3);        % Minimum motor Voltage (V)
Vs_max = Vbat_max / sqrt(3);        % Maximum motor Voltage (V)
Vs_nom = Vbat_nom / sqrt(3);        % Nominal motor Voltage (V)

fsw = 50e3;                         % Inverter maximum switching Frequency (Hz)

K_FW = 0.80;                        % Field Weakening Factor [0.7 .. 0.95]

% Pole number calculation
f_max = fsw / 40;
pp = floor(60 * f_max / wm_max_rpm);
n = 2 * pp;

% Constant power region
wm_nom = P_max / Te_max;
wm_nom_rpm = wm_nom * 60 / (2 * pi);
Te_wm_max = P_max / wm_max;



epsilon = 1.5; % Should be an output, but we lack one equation and we can take similar motors' saliency ratios

% Initial guesses for optimization
lambda_guess = 0.05;
Ld_guess = 0.0001;
Lq_guess = 0.0001;
Is_max_guess = 100;
gamma_MTPA_guess = pi/2;
gamma_FW_guess = pi;

%{
Equations:
eqn 1 --> Te_max = (3/2)*(n/2)*(lambda*Is_max*sin(gamma_MTPA)+(Ld-Lq)*Is_max^2*sin(gamma_MTPA)*cos(gamma_MTPA))
          We look for the MTPA working point, where Is_max at gamma_MTPA gives exactly Te_max

eqn 2 --> 0 = lambda*Is_max*cos(gamma_MTPA)+(Ld-Lq)*Is_max^2*(cos(gamma_MTPA)^2-sin(gamma_MTPA)^2)
          In order to find a relationship between Is_max and gamma_MTPA we write the condition for MTPA: dTe/dgamma = 0

eqn 3 --> Te_wm_max = (3/2)*(n/2)*(lambda*Is_max*sin(gamma_FW)+(Ld-Lq)*Is_max^2*sin(gamma_FW)*cos(gamma_FW))
          In order to aim for the constant power region, we find a working point in which Is_max at gamma_FW gives Te_wm_max

eqn 4 --> (Vs_max/((n/2)*wm_max))^2 >= (lambda + Ld*Is_max*cos(gamma_FW))^2 + (Lq*Is_max*sin(gamma_FW))^2
          The FW working point (Is_max at gamma_FW) should be inside (>=) the voltage ellipse at wm_max 

eqn 5 --> (Vs_max/((n/2)*wm_nom))^2 >= (lambda + Ld*Is_max*cos(gamma_MTPA))^2 + (Lq*Is_max*sin(gamma_MTPA))^2
          The MTPA working point (Is_max at gamma_MTPA) should be inside (>=) the voltage ellipse at wm_nom

%}

% Initial guess for optimization
x0 = [
    lambda_guess;
    Ld_guess;
    Lq_guess;
    Is_max_guess;
    gamma_MTPA_guess;
    gamma_FW_guess
    ];

% Define the equations
F = @(x) [
    -Te_max + (3/2) * (n/2) * (x(1) * x(4) * sin(x(5)) + (x(2) - x(3)) * x(4)^2 * sin(x(5)) * cos(x(5)));
    -0 + x(1) * x(4) * cos(x(5)) + (x(2) - x(3)) * x(4)^2 * (cos(x(5))^2 - sin(x(5))^2);
    -Te_wm_max + (3/2) * (n/2) * (x(1) * x(4) * sin(x(6)) + (x(2) - x(3)) * x(4)^2 * sin(x(6)) * cos(x(6)));
    -(Vs_nom * K_FW / ((n/2) * wm_max))^2 + (x(1) + x(2) * x(4) * cos(x(6)))^2 + (x(3) * x(4) * sin(x(6)))^2;
    -(Vs_nom * K_FW / ((n/2) * wm_nom))^2 + (x(1) + x(2) * x(4) * cos(x(5)))^2 + (x(3) * x(4) * sin(x(5)))^2;
    -epsilon + x(3) / x(2)
];

options = optimoptions('fsolve', 'MaxFunctionEvaluations', 10000);

% Solve the equations
[x_sol, ~, exitflag] = fsolve(F, x0, options);

% Check if the optimization was successful
if exitflag <= 0
    error('Optimization did not converge to a solution.');
end

% Extract optimized values
lambda_sol = x_sol(1);
Ld_sol = x_sol(2);
Lq_sol = x_sol(3);
Is_max_sol = x_sol(4);
gamma_MTPA_sol = x_sol(5);
gamma_FW_sol = x_sol(6);

% Create a symbolic variable for speed (wm)
syms wm

% Define the electromagnetic torque equation
Te_plot = piecewise(wm < wm_nom_rpm, Te_max, wm > wm_nom_rpm, P_max / (wm * 2 * pi / 60));

% Plot the electromagnetic torque
fplot(Te_plot, 'LineWidth', 2, 'Color','r');
title('Electromagnetic Torque vs. Speed', 'FontSize', 14);
xlabel('Speed (RPM)', 'FontSize', 12);
ylabel('Electromagnetic Torque (Nm)', 'FontSize', 12);

% Customize plot appearance
xlim([0, wm_max_rpm]);
ylim([0, Te_max * 1.5]);
grid on;
grid minor;

% Display motor parameters
fprintf('MOTOR PARAMETERS\n');
fprintf('n = %.0f, pp = %.0f\n', [n, pp]);
fprintf('lambda_sol = %.6f Wb\n', lambda_sol);
fprintf('Ld_sol = %.4fe-3 H\n', Ld_sol * 1e3);
fprintf('Lq_sol = %.4fe-3 H\n', Lq_sol * 1e3);
fprintf('Is_max_sol = %.4f A\n', Is_max_sol);
fprintf('gamma_MTPA_sol = %.4f rad\n', gamma_MTPA_sol);
fprintf('gamma_FW_sol = %.4f rad\n', gamma_FW_sol);
