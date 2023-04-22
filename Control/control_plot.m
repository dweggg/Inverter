clc, clear

%% Permanent magnet synchronous machine constant parameters
lambda = 35e-3;                         % [Wb] PM flux linkage
Ld =  0.2372e-3;                        % [H] d-axis inductance
Lq =  0.4459e-3;                        % [H] q-axis inductance
epsilon = Lq/Ld;                        % [ad] Saliency ratio
Rs = 0.0201;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
n = 6;                                  % [ad] Number of poles 
J = 0.01;                               % [N·m^2] Rotor moment of inertia
B = 0.005;                              % [ad] Rotor viscous friction coefficient
P_max = 35e3;                           % [W] Maximum output power
maxRPM = 25000;                         % [rpm] Motor maximum angular speed
Vb = lambda * maxRPM*(2*pi/60) / (n/2); % [V] Base voltage
Vbat = 600;                             % [V] Battery DC voltage
Vs_max = Vbat / (sqrt(3)*Vb);           % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
Is_max = 0.05 * P_max / Vs_max;         % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))

%% Commands
Te_command = 8;
speed_command = 7500*2*pi/60;
%% dq plot
idiq = figure;

id_lim = [-200, 50];
iq_lim = [-200, 200];

axis([id_lim, iq_lim])             % [A] Current maximum values
xlabel('i_d [A]') 
ylabel('i_q [A]') 
grid on
ax = gca;
ax.DataAspectRatio = [1 1 1];
ax.GridLineStyle = '--';
ax.GridAlpha = 0.5;
ax.XAxisLocation="origin";
ax.YAxisLocation="origin";

%% Torque curves & heatmap

hold on

tic
Te_vals = [-50, -26, -20, -5, -1, 1, 5, 20, 26, 50]; % [Nm] Torque values

%id = id_lim(1):1:id_lim(2);
%iq = iq_lim(1):1:iq_lim(2);
    
%tq_color_plot = pcolor(id, iq, abs((3/2)*(n/2)*(lambda.*iq'+(Ld-Lq).*iq'.*id)));

%set(tq_color_plot, 'EdgeColor', 'none');
%colorbar
%colormap(parula)
syms id

for i = 1:length(Te_vals)
    tq_plot = fplot(4*Te_vals(i)/(3*n*(lambda+(Ld-Lq)*id)), 'k', 'LineWidth', 0.75); % IPMSM torque equation, solved for iq
    text(-50, 4*Te_vals(i)/(3*n*(lambda+(Ld-Lq)*-50)), sprintf('%.f N·m',Te_vals(i)),'Color','black','FontSize',12)
end

fplot(4*Te_command/(3*n*(lambda+(Ld-Lq)*id)), 'r', 'LineWidth', 1.5); % IPMSM torque equation, solved for iq
text(-50, 4*Te_command/(3*n*(lambda+(Ld-Lq)*-50)), sprintf('%.f N·m',Te_command),'Color','red','FontSize',14)

clear id iq
toc
%% Current limit circle

alpha = linspace(0,2*pi);
i_lim_plot = plot(Is_max*cos(alpha), Is_max*sin(alpha), '--r', 'LineWidth',3);

clear alpha


%% MTPA curve

Te_vals = [-50:.5:-.1 .1:.5:50]; % More torque values, excluding 0
iq_ref_MTPA = zeros(1,length(Te_vals));

% Iq_ref from torque, MTPA. Extracted from
% https://iris.unipa.it/retrieve/handle/10447/406125/862725/document.pdf,
% eqn 9

% TODO: Hyperbola parametrization
tic
syms iq
for i = 1:length(Te_vals)
    eqn = iq^4 + iq*Te_vals(i)*lambda/((3/2)*(n/2)*(Ld-Lq)^2) - Te_vals(i)^2/(((3/2)*(n/2)*(Ld-Lq))^2);
    solutions = vpasolve(eqn, iq);
    real_sols = real(solutions(imag(solutions) == 0));
    iq_ref_MTPA(i) = double(real_sols(sign(Te_vals(i))*real_sols>0));

end
toc

clear iq eqn solutions real_sols

% Id_ref from Iq_ref, MTPA. Extracted from
% https://iris.unipa.it/retrieve/handle/10447/406125/862725/document.pdf,
% eqn 10
id_ref_MTPA = -lambda/(2*(Ld-Lq)) - sqrt((lambda/(2*(Ld-Lq)))^2+iq_ref_MTPA.^2);

for i = 1:length(Te_vals)
    if abs(Te_vals(i)) <= Te_command*sign(Te_vals(i))
       MTPA_plot = plot(id_ref_MTPA(i), iq_ref_MTPA(i), '+r', 'LineWidth',2);
    else
        MTPA_plot = plot(id_ref_MTPA(i), iq_ref_MTPA(i), '.b', 'LineWidth',1);
    end

end

%% Voltage ellipse

speed_vals = [linspace(0, maxRPM*2*pi/60, 6) speed_command];

% Voltage ellipse eqn
% (id-lambda/Ld)^2/(Vs_max/(Ld*speed))^2+iq^2/(Vs_max/(Lq*speed))^2<=1
for i = 1:length(speed_vals)

    h_ellipse = -lambda/Ld;
    a_ellipse = Vs_max./(Ld.*speed_vals(i));
    b_ellipse = Vs_max./(Lq.*speed_vals(i));
    
    t=-pi:0.01:pi;
    
    id=h_ellipse+a_ellipse.*cos(t);
    iq=b_ellipse.*sin(t);
    if i == length(speed_vals)
        plot(id, iq, '--r','LineWidth',2);
        text(h_ellipse, min(iq), sprintf('%.f rpm',speed_vals(i)*60/(2*pi)),'Color','red','FontSize',14);

    else
        voltageEllipse_plot = plot(id, iq, '--k','LineWidth',1);
        text(h_ellipse, min(iq), sprintf('%.f rpm',speed_vals(i)*60/(2*pi)),'Color','black','FontSize',12);

    end
end

%% Plot legend

legend([i_lim_plot(1), tq_plot(1), MTPA_plot(1), voltageEllipse_plot(1)], 'Current limit [A]', 'Torque curves', 'MTPA hyperbola', 'Voltage limit ellipses')
% TODO: speed limit, FW, MTPV