%% Temperature sensing LUT calculation for DFS05HF12EYR1
clc, clear, close all
%% Initial variables
temperatures = 0.1:0.1:90.1; % Temperature array, 0.01ºC resolution [ºC]

%% NTC Parameters
% DFS05HF12EYR1 internal NTC
% Beta is a function of temperature
beta_values = [3375, 3411, 3433]; % Beta values for different temperatures [K]
beta_temps = [50, 80, 100]; % Temperatures for the different beta values [ºC]

beta_coeffs = polyfit(beta_temps, beta_values, 1); % Fit the beta deviation with linear regression

beta_temp = polyval(beta_coeffs,log(temperatures)); % Beta is evaluated for all temperatures [K]

T_0 = 25; % T at which NTC = R0 [ºC]

R_0 = 5e3; % NTC resistance value at T_0 [Ω]

%% Calculations

% NTC resistance value for all temperatures, with varying beta
NTC = R_0*exp(-beta_temp.*(1./(273.15+25)-1./(273.15+temperatures))); % NTC resistance with no errors [Ω]

% Reading using UCC21732 isolated analog reading. 200uA current source (https://www.ti.com/lit/ds/symlink/ucc21710-q1.pdf?ts=1701352389228&ref_url=https%253A%252F%252Fwww.google.com%252F)
R_filt = 10e3; % Filter resistance, in series with the NTC [Ω]

I_AIN = 200e-6; % Internal current source [A]
V_AIN = I_AIN * (R_filt + NTC); % Sensed voltage [V]

D = -20 * V_AIN + 100; % Duty cycle out [%]

VCC_GD = 5; % GD supply voltage [V]
V_read = VCC_GD * D/100; % Voltage read by ADC [V]

VCC_ADC = 3.3; % MCU/ADC supply voltage [V]
bits = 12; % ADC bits [b]

bits_read = ceil(V_read * (2^bits) / VCC_ADC); % MCU/ADC read bits [b]
bits_read(bits_read>2^bits)=2^bits;
bits_read(bits_read<0)=0;

plot(temperatures, bits_read)

OUTPUT_LUT = [temperatures; bits_read];