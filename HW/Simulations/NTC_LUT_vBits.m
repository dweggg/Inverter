%% Temperature sensing LUT calculation for DFS05HF12EYR1
clc, clear
%% Initial variables

VCC_ADC = 3.3; % MCU/ADC supply voltage [V]
bits = 12; % ADC bits [b]

% Reading using UCC21732 isolated analog reading. 200uA current source (https://www.ti.com/lit/ds/symlink/ucc21710-q1.pdf?ts=1701352389228&ref_url=https%253A%252F%252Fwww.google.com%252F)
VCC_GD = 5; % GD supply voltage [V]
R_filt = 10e3; % Filter resistance, in series with the NTC [Ω]
I_AIN = 200e-6; % Internal current source [A]


bits_read = 0:1:2^bits-1; % ADC bits array [b]

%% Calculations

V_read = bits_read*VCC_ADC/(2^bits); % Voltage read by ADC for all read bits[V] (filtered with ideal RC)

D = V_read*100/VCC_GD; % Duty cycle out  for all read bits[%]

V_AIN = (D - 100)/(-20); % Voltage read by UCC21732 AIN for all read bits [V]

NTC = V_AIN / I_AIN - R_filt; % NTC resistance for all read bits[Ω]
NTC(NTC<1)=1; % Saturation to 1 ohm

%% NTC Parameters

% DFS05HF12EYR1 internal NTC
% Beta is a function of temperature

%beta_values = [3375, 3411, 3433]; % Beta values for different temperatures [K]
%beta_temps = [50, 80, 100]; % Temperatures for the different beta values [ºC]

% CAB016M12FM3 internal NTC
% Beta is a function of temperature
beta_values = [3380, 3468, 3523]; % Beta values for different temperatures [K]
beta_temps = [50+273.15, 80+273.15, 100+273.15]; % Temperatures for the different beta values [ºC]

% Both very similar, interchangable

beta_coeffs = polyfit(beta_temps, beta_values, 1); % Fit the beta deviation with linear regression

T_0 = 25; % T at which NTC = R0 [ºC]

R_0 = 5e3; % NTC resistance value at T_0 [Ω]

syms T
temp_fun = R_0*exp(-(T*beta_coeffs(1)+beta_coeffs(2))*(1/(T_0+273.15)-1/(T)))-NTC;
temperatures = zeros(1, length(temp_fun));
for i = 1:length(temp_fun)
    sol = vpa(solve(temp_fun(i),T))-273.15;
    temperatures(i) = sol(2);
end

%% Create the plot
figure;
plot(temperatures, bits_read, 'LineWidth', 4);

% Add labels and title
xlabel('Temperature (°C)', 'FontSize', 12);
ylabel('Bits Read', 'FontSize', 12);
title('Bits Read vs. Temperature', 'FontSize', 14);

% Add grid and adjust limits
grid on;
xlim([min(temperatures)-5, max(temperatures)+5]);
ylim([min(bits_read)-50, max(bits_read)+50]);

% Customize the appearance
set(gca, 'FontSize', 10); % Adjust font size for axis labels
set(gca, 'LineWidth', 1.5); % Adjust axis line width

OUTPUT_LUT = [temperatures; bits_read];