clear all

Nsamples = 41500;
EulerSaved = zeros(Nsamples, 3);

dt = 0.01;

for k=1:Nsamples
    [p, q, r] = GetGyro();
    [ax, ay, az] = GetAccel();
    [phi_a, theta_a] = EulerAccel(ax, ay, az);
    [phi, theta, psi] = EulerEKF([phi_a, theta_a]', [p, q, r], dt);

    EulerSaved(k, :) = [phi, theta, psi];
end

radtodeg = EulerSaved .* (180/pi); % radian to degree

t = 0:dt:(Nsamples*dt - dt);

ylabel_list = ["Roll angle[deg]", "Pitch angle[deg]", "Yaw angle[deg]"];

figure(1);
for j=1:3
    subplot(3, 1, j);
    plot(t, radtodeg(:, j));
    xlabel('Time [sec]')
    ylabel(ylabel_list(j))
    grid on;
end

saveas(gcf, "Euler angle(by EKF).png")