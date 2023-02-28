clear all


dt = 0.05;
t = 0:dt:20;

Nsamples = length(t);

Xsaved = zeros(Nsamples, 3);
Zsaved = zeros(Nsamples, 1);

for k=1:Nsamples
    r = GetRadar(dt);

    [pos, vel, alt] = RadarPF(r, dt);

    Xsaved(k, :) = [pos, vel, alt];
    Zsaved(k) = r;
end

PosSaved = Xsaved(:, 1);
VelSaved = Xsaved(:, 2);
AltSaved = Xsaved(:, 3);

VelTruth = 100.0 * ones(1, length(VelSaved));
AltTruth = 1000.0 * ones(1, length(AltSaved));

t = 0:dt:Nsamples*dt-dt;

figure(1);

subplot(3, 1, 1);
plot(t, PosSaved);
xlabel('Time[sec]');
ylabel('Position[m]');

subplot(3, 1, 2);
plot(t, VelSaved);
hold on;
plot(t, VelTruth, 'r-');
xlabel('Time[sec]');
ylabel('Velocity[m/s]');
legend('Velocity(PF)', 'Ground Truth')

subplot(3, 1, 3);
plot(t, AltSaved);
hold on;
plot(t, AltTruth, 'r-');
xlabel('Time[sec]');
ylabel('Altitude[m]');
legend('Altitude(PF)', 'Ground Truth')


saveas(gcf, 'result.png');