[kl, Tl] = motorIdentif('motorLeftIdentif.csv');
title('Left motor step response under no load');
[kll, Tll] = motorIdentif('motorLeftIdentifLoad.csv')
title('Left motor step response under platform load');
[kr, Tr] = motorIdentif('motorRightIdentif.csv')
title('Right motor step response under no load');
[krl, Trl] = motorIdentif('motorRightIdentifLoad.csv')
title('Right motor step response under platform load');

figure
s = tf('s'); 
motRight = kr / (s + Tr);
pole = 0.005;
motRight = motRight * (s + pole)/s;
motRight.TimeUnit = 'milliseconds';
rlocus(motRight)
title('Root Locus pole < T');

figure
s = tf('s'); 
motRight = kr / (s + Tr);
pole = 0.05;
motRight = motRight * (s + pole)/s;
motRight.TimeUnit = 'milliseconds';
rlocus(motRight)
title('Root Locus pole > T');

function [kv, T] = motorIdentif(csv_name)
    figure()
    objectResponse = csvread(csv_name);
    t = objectResponse(:, 1);
    y = objectResponse(:, 2);
    plot(t, y);
    hold on;
    coeffs = polyfit(t(31:86), y(31:86), 1);
    fittedX = linspace(min(t), max(t), 200);
    fittedY = polyval(coeffs, fittedX);
    plot(fittedX, fittedY);
    hold off;
    ylim([0 inf]);
    xlabel('time (ms)');
    ylabel('step response (slot count)');
    T = -coeffs(1) / coeffs(2);
    kv = coeffs(1);
end