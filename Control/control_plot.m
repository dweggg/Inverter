clc, clear

%% Permanent magnet synchronous machine constant parameters
% motor = 'e-Tech 2023';
% motor = 'e-Tech 2017';
% motor = 'Silence';
% motor = 'Caruso 2019';
motor = 'AMK';

switch motor
    case 'e-Tech 2023'
        Ke = 0.13;                              % [V/(rad/s)] Mechanical speed constant
        n = 6;                                  % [ad] Number of poles 
        lambda_Ke = Ke / sqrt(3);               % [Wb] PM flux linkage
        lambda = 28.95e-3;                      % [Wb] PM flux linkage
        Ld =  0.1269e-3;                        % [H] d-axis inductance
        Lq =  0.2268e-3;                        % [H] q-axis inductance
        epsilon = Lq/Ld;                        % [ad] Saliency ratio
        Rs = 0.0201;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
        P_max = 35e3;                           % [W] Maximum output power
        SpeedMax = 20000;                       % [rpm] Motor maximum angular speed
        Te_max = 26;                            % [N·m] Motor maximum angular torque
        Vbat = 580;                             % [V] Battery DC voltage
        Vs_max = Vbat / sqrt(3);                % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
        Is_max = 185;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
        Te_command = 26;
        SpeedRef = 20000*2*pi/60;  
    case 'e-Tech 2017'
        Ke = 49.7e-3*60/(2*pi);                 % [Vrms,phph/(rad/s)] Speed constant, Vrms,phph/wm
        n = 8;                                  % [ad] Number of poles 
        lambda = Ke / (sqrt(3) * (n/2));        % [Wb] PM flux linkage, Vrms,phn/we
        Ld =  0.520e-3;                         % [H] d-axis inductance
        Lq =  1.265e-3;                         % [H] q-axis inductance
        epsilon = Lq/Ld;                        % [ad] Saliency ratio
        Rs = 0.104/2;                           % [Ohm] Stator phase resistance (phase-to-phase/2)
        P_max = 60e3;                           % [W] Maximum output power
        SpeedMax = 6000;                        % [rpm] Motor maximum angular speed
        Te_max = 150;                           % [N·m] Motor maximum angular torque
        Vbat = 580;                             % [V] Battery DC voltage
        Vs_max = Vbat / sqrt(3);                % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
        Is_max = 200;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
        Te_command = 80;
        SpeedRef = 7500*2*pi/60;  
    case 'Silence'
        n = 40;                                 % [ad] Number of poles 
        lambda = 0.02282824;                    % [Wb] PM flux linkage
        Ld =  70e-6;                            % [H] d-axis inductance
        Lq =  79e-6;                            % [H] q-axis inductance
        epsilon = Lq/Ld;                        % [ad] Saliency ratio
        Rs = 0.017;                             % [Ohm] Stator phase resistance (phase-to-phase/2)
        SpeedMax = 1000;                        % [rpm] Motor maximum angular speed
        Te_max = 80;                            % [N·m] Motor maximum angular torque
        Vbat = 48;                              % [V] Battery DC voltage
        Vs_max = Vbat / sqrt(3);                % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
        Is_max = 156;                           % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))      
        Te_command = 66;
        SpeedRef = 500*2*pi/60;
    case 'Caruso 2019'
        n = 6;                                 % [ad] Number of poles 
        lambda = 0.084;                        % [Wb] PM flux linkage
        Ld =  9.77E-3;                         % [H] d-axis inductance
        Lq =  14.94E-3;                        % [H] q-axis inductance
        epsilon = Lq/Ld;                       % [ad] Saliency ratio
        Rs = 2.21;                             % [Ohm] Stator phase resistance (phase-to-phase/2)
        SpeedMax = 4300;                       % [rpm] Motor maximum angular speed
        Te_max = 2;                            % [N·m] Motor maximum angular torque
        Vbat = 310;                            % [V] Battery DC voltage
        Vs_max = Vbat / sqrt(3);               % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
        Is_max = 3.6*2;                        % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
        Is_max = 8.5;
        Te_command = 1.8;
        SpeedRef = 380;

    case 'AMK'
        n = 10;                                % [ad] Number of poles 
        kE = 18.8;                             % [Vrmsphn/krpm(wm)] Speed constant 
        lambda = kE*(60/(2*pi))/(1000*(n/2));  % [Wb] PM flux linkage
        Ld =  0.12e-3;                         % [H] d-axis inductance
        Lq =  0.24e-3;                         % [H] q-axis inductance
        epsilon = Lq/Ld;                       % [ad] Saliency ratio
        Rs = 0.135;                            % [Ohm] Stator phase resistance (phase-to-phase/2)
        SpeedMax = 20000;                      % [rpm] Motor maximum angular speed
        Te_max = 30;                           % [N·m] Motor maximum angular torque
        Vbat = 560;                            % [V] Battery DC voltage
        Vs_max = Vbat / sqrt(3);               % [V] Maximum d-q voltage (Maximum Torque per Voltage Flux-Weakening strategy with speed limiter for PMSM drives, 2020)
        Is_max = 105;                          % [A] Maximum d-q current (sqrt(i_d^2+i_q^2))
        Te_command = 21;
        SpeedRef = 25000*2*pi/60;
    otherwise
end


%% dq plot
idiq = figure;

id_lim = [-Is_max-50, 50];
iq_lim = [-Is_max-50, +Is_max+50];

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

%% Torque curves

hold on

tic
Te_vals = linspace(-Te_max, Te_max, 7); % [Nm] Torque values
Te_vals = Te_max;
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

Te_vals = linspace(-Te_max*2, Te_max*2, 100); % [Nm] 100 Torque values;
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
I_ck = lambda/Ld;
h_ellipse = -I_ck;
speed_vals = [linspace(0.001, SpeedMax*2*pi/60, 6), SpeedRef]; % speed values
% Voltage ellipse eqn
% (id+lambda/Ld)^2/(Vs_max/(Ld*speed))^2+iq^2/(Vs_max/(Lq*speed))^2<=1

for i = 1:length(speed_vals)

    h_ellipse = -I_ck;
    a_ellipse = Vs_max./(Ld.*(n/2)*speed_vals(i));
    b_ellipse = Vs_max./(Lq.*(n/2)*speed_vals(i));
    
    t=0:0.01:2*pi;
    
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