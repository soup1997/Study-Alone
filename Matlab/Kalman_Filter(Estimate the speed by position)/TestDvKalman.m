clear

% To estimate the speed by position %
dt = 0.1;
t = 0:dt:10;

Nsamples = length(t);

Xsaved = zeros(Nsamples, 2);
Zsaved = zeros(Nsamples, 1);
Ground_truth = zeros(Nsamples, 2);

for k = 1:Nsamples
    [z, posp, velp] = GetPos();
    [pos, vel] = DvKalman(z);

    Xsaved(k, :) = [pos, vel];
    Zsaved(k) = z;
    Ground_truth(k, :) = [posp, velp];

end

figure(1);
hold on;
plot(t, Zsaved, 'r.');
plot(t, Xsaved(:, 1));
plot(t, Ground_truth(:, 1), 'b-');
legend('Measurements', 'Kalman Filter', "Ground Truth", "Location", 'northwest');
xlabel('Time [sec]');
ylabel('Position [m]');
grid on;
hold off;
saveas(gcf, 'Position.png')

figure(2);
hold on;
plot(t, Xsaved(:, 2), 'r');
plot(t, Ground_truth(:, 2), 'b:*')
xlabel('Time [sec]');
ylabel('Velocity [m/s]');
legend("Kalman Filter", "Groud Truth")
grid on;
hold off;
saveas(gcf, 'Velocity.png')