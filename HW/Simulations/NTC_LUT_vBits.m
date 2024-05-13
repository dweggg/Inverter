%% Temperature sensing LUT calculation for DFS05HF12EYR1
clc, clear, close all
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

temperatures = -273.15-(-beta_coeffs(1)*(T_0+273.15)+(T_0+273.15)*log(NTC/R_0)+beta_coeffs(2)-sqrt(((T_0+273.15)*beta_coeffs(1)).^2+((T_0+273.15)*log(NTC/R_0)).^2+2*(T_0+273.15)*beta_coeffs(1)*beta_coeffs(2)+2*beta_coeffs(2)*(T_0+273.15)*log(NTC/R_0)-2*beta_coeffs(1)*(T_0+273.15).^2*log(NTC/R_0)+beta_coeffs(2).^2))/(2*beta_coeffs(1));

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


% Format OUTPUT_LUT in a string suitable for C
output_str = sprintf('\n// Output Lookup Table (Temperatures vs. NTC Resistances)\n');

% Create the NTC_LUT_bits and NTC_LUT_temps arrays
NTC_LUT_bits = OUTPUT_LUT(2, :); % NTC Resistances
NTC_LUT_temps = OUTPUT_LUT(1, :); % Temperatures

% Number of elements in the LUT
lut_size = numel(NTC_LUT_bits);

% Convert to integer for NTC_LUT_bits
NTC_LUT_bits_int = round(NTC_LUT_bits);

% Print the formatted string
output_str = [output_str, '// const int NTC_LUT_bits[] = {'];
output_str = [output_str, sprintf('%d, ', NTC_LUT_bits_int(1:end-1))];
output_str = [output_str, sprintf('%d};\n', NTC_LUT_bits_int(end))];

output_str = [output_str, sprintf('// NTC_LUT_bits is just an array 0, 1, 2... 4094, 4095 so no need to store that, just here for clarification\n')];

output_str = [output_str, 'const float tempLUT[] = {'];
output_str = [output_str, sprintf('%.2f, ', NTC_LUT_temps(1:end-1))];
output_str = [output_str, sprintf('%.2f};\n', NTC_LUT_temps(end))];

% Specify the file name
filename = 'output_LUT.txt';

% Write the string to the text file
fid = fopen(filename, 'w');
fprintf(fid, '%s', output_str);
fclose(fid);

disp(['Output saved to: ', filename]);
