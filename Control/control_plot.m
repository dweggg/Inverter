clc, clear

%% Permanent magnet synchronous machine constant parameters
lambda = 0.06711353021;                 % [Wb] PM flux linkage
Ld = 0.52e-3;                           % [H] d-axis inductance
Lq = 1.26e-3;                           % [H] q-axis inductance
epsilon = Lq/Ld;                        % [ad] Saliency ratio
Rs = 104e-3;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
n = 8;                                  % [ad] Number of poles 
J = 0.01;                               % [N·m^2] Rotor moment of inertia
B = 0.005;                              % [ad] Rotor viscous friction coefficient
maxRPM = 20000;                         % [rpm] Motor maximum angular speed
Is_max = 125;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
Vb = lambda * maxRPM*(2*pi/60) / (n/2); % [V] Base voltage
Vbat = 500;                             % [V] Battery DC voltage
Vs_max = Vbat / (sqrt(3)*Vb);           % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)

%% dq plot
idiq = figure;

id_lim = [-200, 50];
iq_lim = [-150, 150];

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
Te_vals = [-150, -120, -50, -20, -5, 5, 20, 50, 120, 150]; % [Nm] Torque values

%id = id_lim(1):1:id_lim(2);
%iq = iq_lim(1):1:iq_lim(2);

%tq_color_plot = pcolor(id, iq, abs((3/2)*(n/2)*(lambda.*iq'+(Ld-Lq).*iq'.*id)));

%set(tq_color_plot, 'EdgeColor', 'none');
%colorbar
%colormap(parula)
syms id

for i = 1:length(Te_vals)
    tq_plot = fplot(sign(Te_vals(i))*sqrt(2*abs(Te_vals(i))/(3*(n/2)*id*lambda*(Ld-Lq))), 'k', 'LineWidth', 1.5); % IPMSM torque equation, solved for iq
    text(-50, sign(Te_vals(i))*sqrt(2*Te_vals(i)/(3*(n/2)*sign(Te_vals(i))*-50*lambda*(Ld-Lq))), sprintf('%.f N·m',Te_vals(i)),'Color','black','FontSize',14)
end

clear id iq
toc

%% Current limit circle

alpha = linspace(0,2*pi);
i_lim_plot = plot(Is_max*cos(alpha), Is_max*sin(alpha), '--r', 'LineWidth',3);

clear alpha


%% MTPA curve

Te_vals = [-150:1:-.1 .1:1:150]; % More torque values, excluding 0
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

clear iq eqn %solutions real_sols

% Id_ref from Iq_ref, MTPA. Extracted from
% https://iris.unipa.it/retrieve/handle/10447/406125/862725/document.pdf,
% eqn 10
id_ref_MTPA = -lambda/(2*(Ld-Lq)) - sqrt((lambda/(2*(Ld-Lq)))^2+iq_ref_MTPA.^2);

for i = 1:length(Te_vals)
    MTPA_plot = plot(id_ref_MTPA(i), iq_ref_MTPA(i), 'xb', 'LineWidth',3);

end

%% Voltage ellipse

speed_vals = [50, 62.5, 75, 100, 150, 200, 500, 800];

% Voltage ellipse eqn
% (id-lambda/Ld)^2/(Vs_max/(Ld*speed))^2+iq^2/(Vs_max/(Lq*speed))^2<=1
for i = 1:length(speed_vals)

    h_ellipse = -lambda/Ld;
    a_ellipse = Vs_max./(Ld.*speed_vals(i));
    b_ellipse = Vs_max./(Lq.*speed_vals(i));
    
    t=-pi:0.01:pi;
    
    id=h_ellipse+a_ellipse.*cos(t);
    iq=b_ellipse.*sin(t);
    
    voltageEllipse_plot = plot(id, iq, 'm','LineWidth',1.5);

    text(h_ellipse, min(iq), sprintf('%.f rad/s',speed_vals(i)),'Color','magenta','FontSize',14);
end

%% Plot legend

legend([i_lim_plot(1), tq_plot(1), MTPA_plot(1), voltageEllipse_plot(1)], 'Current limit [A]', 'Torque curves', 'MTPA hyperbola', 'Voltage limit ellipses')
% TODO: Voltage ellipse, speed limit, FW, MTPV