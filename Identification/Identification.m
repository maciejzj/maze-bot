% Get object parameters based on step response in csv file
% and print the response of each motor.
[kl, Tl] = motorIdentif('motorLeftIdentif.csv');
title('Left motor step response under no load');
[kll, Tll] = motorIdentif('motorLeftIdentifLoad.csv')
title('Left motor step response under platform load');
[kr, Tr] = motorIdentif('motorRightIdentif.csv')
title('Right motor step response under no load');
[krl, Trl] = motorIdentif('motorRightIdentifLoad.csv')
title('Right motor step response under platform load');

% Plot root locus for right motor (which acts as slave).
% First option for pole c < T
figure
s = tf('s'); 
motRight = kr / (s + Tr);
c = Tr - 0.005;
motRight = motRight * (s + c)/s;
motRight.TimeUnit = 'milliseconds';
rlocus(motRight)
title('Root Locus, pole c < T');

% Second option for pole c > T
figure
s = tf('s'); 
motRight = kr / (s + Tr);
c = Tr + 0.005;
motRight = motRight * (s + c)/s;
motRight.TimeUnit = 'milliseconds';
rlocus(motRight)
title('Root Locus, pole c > T');

% Motor identification function, presumes integrating model.
function [kv, T] = motorIdentif(csv_name)
    % Plot step response.
    figure()
    objectResponse = csvread(csv_name);
    t = objectResponse(:, 1);
    y = objectResponse(:, 2);
    plot(t, y);
    hold on;
    % Fit line to the middle part of the step response.
    coeffs = polyfit(t(31:86), y(31:86), 1);
    fittedX = linspace(min(t), max(t), 200);
    fittedY = polyval(coeffs, fittedX);
    % Plot fitted line.
    plot(fittedX, fittedY);
    hold off;
    ylim([0 inf]);
    xlabel('time (ms)');
    ylabel('step response (slot count)');
    % Calculate and return object transfer function parameters.
    T = -coeffs(1) / coeffs(2);
    kv = coeffs(1);
end