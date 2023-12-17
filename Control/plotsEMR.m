% Simulink Output Plotting Script

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

% Load Simulink output data
load('EMR_out.mat');  % Update with your Simulink output file name

% Plot Tem
figure;
plot(out.Tem, 'LineWidth', 1, 'Color', 'k');

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$T_{em}$ [N$\cdot$m]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Electromagnetic Torque ($T_{em}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/Tem_plot.png');

% Plot id,iq
figure;
hold on
plot(out.idiq.Time, out.idiq.Data(:,1), 'LineWidth', 1, 'Color', 'r');
plot(out.idiq.Time, out.idiq.Data(:,2), 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$I_{d} - I_{q}$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Currents ($I_{d} - I_{q}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$I_d$', '$I_q$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/idiq_plot.png');

%{
% Plot id,iq PI up to 0.1s
figure;
hold on
time_index = out.idiq_ct.Time <= 0.1;

plot(out.idiq_ct.Time(time_index), out.idiq_ct.Data(time_index, 1), 'LineWidth', 1, 'Color', 'r');
plot(out.idiq_ct.Time(time_index), out.idiq_ct.Data(time_index, 2), 'LineWidth', 1, 'Color', 'r');

plot(out.idiq_ct.Time(time_index), out.idiq_ct.Data(time_index, 3), 'LineWidth', 1, 'Color', 'k');
plot(out.idiq_ct.Time(time_index), out.idiq_ct.Data(time_index, 4), 'LineWidth', 1, 'Color', 'k');

hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$I_{d} - I_{q}$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Currents ($I_{d} - I_{q}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$I_d,ref$', '$I_q,ref$', '$I_d$', '$I_q$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/idiq_plot.png');
%}

% Plot id-iq
figure;
plot(out.idiq.Data(:,1), out.idiq.Data(:,2), 'LineWidth', 1, 'Color', 'k');

xlabel('$I_{d}$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$I_{q}$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Currents ($I_{d} - I_{q}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/id-iq_plot.png');

% Convert wm to rpm without scientific notation and decimals
out.wm.Data = round(out.wm.Data * (60 / (2 * pi)));

% Plot wm-Tem
figure;
plot(out.wm.Data, out.Tem.Data, 'LineWidth', 1, 'Color', 'k');

xlabel('$\omega_{m}$ [rpm]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$T_{em}$ [N$\cdot$m]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Mechanical Speed ($\omega_{m}$) vs Electromagnetic Torque ($T_{em}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/wm_Tem_plot.png');

% Plot wm
figure;
plot(out.wm, 'LineWidth', 1, 'Color', 'k');

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$\omega_{m}$ [rpm]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Mechanical Speed ($\omega_{m}$)', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/wm_plot.png');

% Plot vdvqPI
figure;
hold on
plot(out.vdvqPI.Time, round(out.vdvqPI.Data(:,1)), 'LineWidth', 1, 'Color', 'r');
plot(out.vdvqPI.Time, round(out.vdvqPI.Data(:,2)), 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$V_{dq}$ [V]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Voltage ($V_{dq}$) from PI Controller', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$V_{d}$', '$V_{q}$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, 'Plots_memoria/vdvqPI_plot.png');


% Plot abc
%{
time_index = out.dabc.Time >= 5.565 & out.dabc.Time <= 5.57;

figure;
subplot(2, 1, 1);
plot(out.dabc.Time(time_index), out.dabc.Data(time_index, :), 'LineWidth', 1);

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$D_a, D_b, D_c$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Duty cycles', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;

subplot(2, 1, 2);
plot(out.vabc.Time(time_index), out.vabc.Data(time_index, :), 'LineWidth', 1);

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$V_a, V_b, V_c$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('AC Voltages', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;

saveas(gcf, 'Plots_memoria/abc_plot.png');
%}