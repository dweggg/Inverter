% Simulation Output Plotting Script

clear, clc, close all

% Set up plotting configurations
styleConfig = struct(...
    'fontConfig', struct(...
        'legendFontSize', 14, ...
        'xlabelFontSize', 16, ...
        'ylabelFontSize', 16, ...
        'titleFontSize', 18, ...
        'ticksFontSize', 12), ...
    'colorVector', [0, 0.4470, 0.7410]);

currentConfig = styleConfig;

% Load simulation output data
load('losses_inv.mat');  % Update with your simulation output file name

% Specify output directory
outputDirectory = 'Plots_memoria_PLECS/';

% Create output directory if it doesn't exist
if ~exist(outputDirectory, 'dir')
    mkdir(outputDirectory);
end

% Plot all available data
columnTitles = ["TR_CL", "TR_SL", "D_CL", "D_SL"];

time = data(1,:);

for col = 1:(length(columnTitles))
    expr = strcat(columnTitles(col),' = data(col+1,:);');
    eval(expr);
end

% Calculate total losses
Total_Losses = TR_CL + TR_SL + D_CL + D_SL;

% Create figure with larger horizontal size
figure('Position', [100, 100, 1600, 600]);  % Adjust the last two values for width and height

% Plot individual losses with different line styles (black)
hold on;
plot(time, TR_CL, 'k-', 'LineWidth', 1);
plot(time, TR_SL, 'k--', 'LineWidth', 1);
plot(time, D_CL, 'k-.', 'LineWidth', 1);
plot(time, D_SL, 'k:', 'LineWidth', 1);

% Plot total losses in red
plot(time, Total_Losses, 'r', 'LineWidth', 1.5);
hold off;

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('Power Loss [W]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Inverter Power Loss Components', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
legend('MOSFET conduction losses', 'MOSFET switching losses', 'Diode conduction losses', 'Diode switching losses', 'Total Losses', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);
grid on;
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

% Save the combined figure
outputDirectory = 'Plots_memoria_PLECS/';
if ~exist(outputDirectory, 'dir')
    mkdir(outputDirectory);
end
saveas(gcf, [outputDirectory, 'Total_Losses.png']);

