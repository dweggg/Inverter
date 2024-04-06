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
load('FOC_CAB0016M12FM3.mat');  % Update with your simulation output file name

% Specify output directory
outputDirectory = 'Plots_memoria_PLECS/';

% Create output directory if it doesn't exist
if ~exist(outputDirectory, 'dir')
    mkdir(outputDirectory);
end

% Plot all available data
columnTitles = ["time2", "M_Id_pk", "M_Iq_pk", "IdRef_pk", "IqRef_pk", "M_Is_pk", "IsRef_pk", "M_gamma", "gammaRef", ...
    "VdRef_pk", "VdRefSat_pk", "VqRef_pk", "VqRefSat_pk", "VsRef_pk", "VsRefsat_pk", "Va", "Vb", "Vc", "Ia", "Ib", ...
    "Ic", "Vdc", "Vdc2", "delta_gammaRef", "gammaRef_MTPA", "gammaRef_abs", "Vlimit_pk", "VsRefFW_pk", "VsRefSat_pk", ...
    "wm_max", "M_wm", "lim_TemRef", "Tem", "TemRefsat", "T_inverter", "P_loss", "P_mot", "P_bat", "Eff_1", "Eff2", ...
    "Eff3", "PF_abc"];

time = data(1,:);

for col = 1:(length(columnTitles)-1)
    expr = strcat(columnTitles(col),' = data(col+1,:);');
    eval(expr);
end

% Plot Id-Iq xy plot (reference and measured)
figure;
hold on
plot(IdRef_pk, IqRef_pk, 'LineWidth', 1, 'Color', 'r');
plot(M_Id_pk, M_Iq_pk, 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('$I_d$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$I_q$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('$I_d - I_q$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$I_d - I_q$, ref', '$I_d - I_q$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, [outputDirectory, 'PLECS_id-iq.png']);

% Plot Id-Iq time plot (reference and measured)
figure;
hold on
plot(time, IdRef_pk, 'LineWidth', 1, 'Color', 'r');
plot(time, M_Id_pk, 'LineWidth', 1, 'Color', 'k');
plot(time, IqRef_pk, 'LineWidth', 1, 'Color', 'r');
plot(time, M_Iq_pk, 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$I_d - I_q$ [A]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('$I_d - I_q$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$I_d$, ref', '$I_d$', '$I_q$, ref', '$I_q$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, [outputDirectory, 'PLECS_idiq.png']);

% Plot Vd-Vq time plot (reference and measured)
figure;
hold on
plot(time, VdRef_pk, 'LineWidth', 1, 'Color', 'r');
plot(time, VdRefSat_pk, 'LineWidth', 1, 'Color', 'k');
plot(time, VqRef_pk, 'LineWidth', 1, 'Color', 'r');
plot(time, VqRefSat_pk, 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$V_d - V_q$ [V]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('$V_d - V_q$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$V_d$, ref', '$V_d$, sat', '$V_q$, ref', '$V_q$, sat'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, [outputDirectory, 'PLECS_vdvq.png']);

% Plot all gammas (reference and measured) time plot
figure;
hold on
plot(time, gammaRef, 'LineWidth', 1, 'Color', 'r');
plot(time, gammaRef_MTPA, 'LineWidth', 1, 'Color', 'r');
plot(time, delta_gammaRef, 'LineWidth', 1, 'Color', 'r');
plot(time, M_gamma, 'LineWidth', 1, 'Color', 'k');
hold off

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('$\gamma$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('$\gamma$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$\gamma$, ref', '$\gamma$, ref, MTPA', '$\Delta\gamma$, ref (FW)','$\gamma$'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize);

ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

saveas(gcf, [outputDirectory, 'PLECS_gamma.png']);

% Assuming you have time, M_wm, TemRefsat, and Tem vectors
fig = figure;
yyaxis left;  % Left y-axis for torque
plot(time, TemRefsat, 'LineWidth', 1, 'Color', 'r');  % Plotting torque reference
hold on;
plot(time, Tem, 'LineWidth', 1, 'Color', 'k');  % Plotting actual torque
ylabel('$T_{em, ref}$ [N$\cdot$m], $T_{em}$ [N$\cdot$m]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);

yyaxis right;  % Right y-axis for speed
plot(time, M_wm*60/2/pi, 'LineWidth', 1, 'Color', 'k');  % Plotting speed
ylabel('$\omega_m$ [rpm]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
title('$\omega_m$ - $T_{em}$', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
legend({'$T_{em}$, ref [N$\cdot$m]', '$T_{em}$ [N$\cdot$m]', '$\omega_m$ [rpm]'}, 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.legendFontSize, 'Location', 'best');
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis(1).Exponent = 0;  % Exponent for left y-axis
ax.YAxis(2).Exponent = 0;  % Exponent for right y-axis
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis(1).TickLabelFormat = '%g';
ax.YAxis(2).TickLabelFormat = '%g';

ax.YAxis(1).Color = [1 0 0];
ax.YAxis(2).Color = [0 0 0];

saveas(gcf, [outputDirectory, 'PLECS_Tem.png']);

% Create a subplot with 2 rows and 1 column
figure;

% Subplot 1: Inverter temperature time plot
subplot(2, 1, 1);
plot(time, T_inverter, 'LineWidth', 1, 'Color', 'k');

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('Inverter Temperature [$^\circ$C]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Inverter Temperature', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

% Subplot 2: Losses time plot
subplot(2, 1, 2);
plot(time, P_loss, 'LineWidth', 1, 'Color', 'k');

xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.xlabelFontSize);
ylabel('Power Loss [W]', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.ylabelFontSize);
title('Inverter Power Loss', 'Interpreter', 'latex', 'FontSize', currentConfig.fontConfig.titleFontSize);
set(gca, 'FontSize', currentConfig.fontConfig.ticksFontSize, 'TickLabelInterpreter', 'latex');
grid on;
ax = gca;
ax.XAxis.Exponent = 0;
ax.YAxis.Exponent = 0;
ax.XAxis.TickLabelFormat = '%g';
ax.YAxis.TickLabelFormat = '%g';

% Save the combined figure
saveas(gcf, [outputDirectory, 'PLECS_thermal.png']);
