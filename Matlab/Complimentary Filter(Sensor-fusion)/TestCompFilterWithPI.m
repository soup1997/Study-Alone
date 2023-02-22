clear all

Nsamples = 41500;

EulerSaved = zeros(Nsamples, 3);

dt = 0.01;

for k = 1:Nsamples
    [ax, ay, az] = GetAccel();
    [p, q, r] = GetGyro();
    [phi, theta, psi] = CompFilterWithPI(p, q, r, ax, ay, az, dt);

    EulerSaved(k, :) = [phi, theta, psi]';
end

PhiSaved = EulerSaved(:, 1) * 180/pi;
ThetaSaved = EulerSaved(:, 2) * 180/pi;
PsiSaved = EulerSaved(:, 3) * 180/pi;

t = 0:dt:Nsamples*dt-dt;

figure(1);
plot(t, PhiSaved);

figure(2);
plot(t, ThetaSaved);

figure(3);
plot(t, PsiSaved);