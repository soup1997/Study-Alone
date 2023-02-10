clear all

dt = 0.05;
t = 0:dt:20;

Nsamples = length(t);

Xsaved = zeros(Nsamples, 3);
Zsaved = zeros(Nsamples, 1);

for k=1:Nsamples
    r = GetRadar(dt);

    [pos, vel, alt] = RadarUKF(r, dt);
    Xsaved(k, :) = [pos, vel, alt];
    Zsaved(k) = r;
end

PosSaved = Xsaved(:, 1);
VelSaved = Xsaved(:, 2);
AltSaved = Xsaved(:, 3);
DistSaved = sqrt(Xsaved(:, 1).^2 + Xsaved(:, 3).^2);

t = 0:dt:Nsamples*dt-dt;

%-------figure 1-------%
figure(1);
ylabel_list = ["Speed [m/s]", "Altitude [m]", "Position [m]"];
for i=1:3
    subplot(3, 1, i)
    plot(t, Xsaved(:, i));
    xlabel('Time [sec]');
    ylabel(ylabel_list{i});
end

saveas(gcf, 'Speed, Altitude, Position.png')

%-------figure 2-------%
figure(2);
plot(t, Zsaved, 'r:')
hold on;
plot(t, DistSaved, 'r-');
xlabel('Time [sec]');
ylabel('Radar distance [m]');
legend('Measured', 'Estimated');
grid on;
saveas(gcf, 'Unscented Kalman Filter(Distance).png')