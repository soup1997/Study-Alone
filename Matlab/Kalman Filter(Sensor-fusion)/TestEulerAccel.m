clear all

Nsamples = 41500;
EulerSaved = zeros(Nsamples, 2);

for k = 1:Nsamples
    [ax, ay, az] = GetAccel();
    [phi, theta] = EulerAccel(ax, ay, az);

    EulerSaved(k, :) = [phi, theta];
end

radtodeg = EulerSaved(:, :) * (180/pi); % radian to degree

dt = 0.01;
t = 0:dt:Nsamples*dt - dt;

ylabel_list = ["Roll angle[deg]", "Pitch angle[deg]"];

figure(1);
for j=1:2
    subplot(2, 1, j);
    plot(t, radtodeg(:, j));
    xlabel('Time [sec]')
    ylabel(ylabel_list(j))
    grid on;
end

saveas(gcf, 'Euler angle(by Accelerometer).png')