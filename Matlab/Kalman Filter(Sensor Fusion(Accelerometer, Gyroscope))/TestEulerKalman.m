clear all;

Nsamples = 41500;
EulerSaved = zeros(Nsamples, 3);

dt = 0.01;

for k=1:Nsamples
    [p, q, r] = GetGyro();
    A = eye(4) + dt*1/2*[0, -p, -q, -r;
                         p, 0, r, -q;
                         q, -r, 0, p;
                         r, q, -p, 0];

    [ax, ay, az] = GetAccel();
    [phi, theta, psi] = EulerAccel(ax, ay, az);
    z = EulerToQuaternion(phi, theta, psi);

    [phi, theta, psi] = EulerKalman(A, z);

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

saveas(gcf, 'Euler angle(by Kalmanfilter).png')