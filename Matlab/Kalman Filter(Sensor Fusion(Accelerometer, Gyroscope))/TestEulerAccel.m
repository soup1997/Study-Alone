clear all

Nsamples = 41500;
EulerSaved = zeros(Nsamples, 3);

for k = 1:Nsamples
    [ax, ay, az] = GetAccel();
    [phi, theta, psi] = EulerAccel(ax, ay, az);

    EulerSaved(k, :) = [phi, theta, psi];
end

radtodeg = EulerSaved(:, :) * (180/pi); % radian to degree

dt = 0.01;
t = 0:dt:Nsamples*dt - dt;

ylabel_list = ["Roll angle[deg]", "Pitch angle[deg]", "Yaw angle[deg]"];

figure(1);
for j=1:3
    subplot(3, 1, j);
    plot(t, radtodeg(:, j));
    xlabel('Time [sec]')
    ylabel(ylabel_list(j))
    grid on;
end

saveas(gcf, 'Euler angle(by Accelerometer).png')