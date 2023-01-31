clear

NoOfImg = 24;

Xmsaved = zeros(2, NoOfImg);
Xhsaved = zeros(2, NoOfImg);

for k = 1:NoOfImg
    [xm, ym] = GetBallPos(k);
    [xh, yh] = TrackKalman(xm, ym);

    hold on;
    plot(xm, ym, 'g*'); % GetBallPos 함수가 측정한 위치 표시(Measured Position)
    plot(xh, yh, 'rs'); % Kalman Filter가 추정한 위치 표시(Estimated Position)
    xlabel('x [pixel]');
    ylabel('y [pixel]');
    pause(1);

    Xmsaved(:, k) = [xm, ym]';
    Xhsaved(:, k) = [xh, yh]';
end

figure(1);
hold on;
plot(Xmsaved(1, :), Xmsaved(2, :), '*');
plot(Xhsaved(1, :), Xhsaved(2, :), 's');
xlabel('y [pixel]');
ylabel('x [pixel]');
legend('Measurements', 'Kalman Filter')
set(gca, 'yDir', 'reverse');
saveas(gcf,'result.png')