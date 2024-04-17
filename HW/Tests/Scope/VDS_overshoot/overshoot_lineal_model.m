% Data points: (voltage, current, overshoot)
clc, clear, close all

Csn = 1

if Csn
    data = [
        10, 0, 10.8;
        10, 0.75, 11.1;
        20, 0, 21.3;
        20, 2*0.75, 21.5;
        30, 0, 31.7;
        30, 3*0.75, 32.3;
        40, 0, 45.9;
        40, 4*0.75, 46.9;
        80, 5.5, 92.6;
        90, 0, 102.5;
        90, 6.2, 104.9;
        120, 0, 135.6;
        150, 0, 172;
        180, 0, 205;
        200, 0, 227;
    ];
else
    data = [
        10, 0, 15;    % 5V overshoot (15Vp) @ 10V 0A
        20, 0, 30;    % 10V overshoot (30Vp) @ 20V 0A
        10, 0.75, 20; % 10V overshoot (20Vp) @ 10V 750mA
        % Add more data points here if needed
    ];

end
% Extracting matrix X and vector Y
X = [data(:,1), data(:,2), ones(size(data,1),1)];
Y = data(:,3);

% Fit a linear model
mdl = fitlm(X, Y, 'linear');

% Display the linear model
disp('Linear Model:');
disp(mdl);

% Extract coefficients
a = mdl.Coefficients.Estimate(2);
b = mdl.Coefficients.Estimate(3);
c = mdl.Coefficients.Estimate(1);

% Display coefficients
disp('Coefficients:');
disp(['a = ', num2str(a)]);
disp(['b = ', num2str(b)]);
disp(['c = ', num2str(c)]);

% Test the linear model with provided data points
for i = 1:size(data,1)
    voltage = data(i,1);
    current = data(i,2);
    overshoot = data(i,3);
    predicted_overshoot = a*voltage + b*current + c;
    
    disp(['Actual Overshoot: ', num2str(overshoot), 'Vp | Predicted Overshoot: ', num2str(predicted_overshoot), 'Vp']);
end


voltage = 600;
current = 80;
predicted_overshoot = a*voltage + b*current + c;

disp(['Predicted Overshoot at 600V 80A: ', num2str(predicted_overshoot), 'Vp']);

% Create a grid for 3D plot
[x1_grid, x2_grid] = meshgrid(0:50:600, 0:5:80);
y_grid = a*x1_grid + b*x2_grid + c;

% 3D plot with colored plane representing linear model
figure;
scatter3(data(:,1), data(:,2), data(:,3), 'filled', 'MarkerFaceColor', 'b');
hold on;
surf(x1_grid, x2_grid, y_grid, 'FaceAlpha', 0.5);
xlabel('Voltage (V)');
ylabel('Current (A)');
zlabel('Overshoot (Vp)');
title('Linear Model and Data Points');
colorbar;
view(3);
hold off;
