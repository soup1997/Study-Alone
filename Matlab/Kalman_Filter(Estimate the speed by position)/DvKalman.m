function [pos, vel] = DvKalman(z)

persistent A H Q R
persistent x_hat P
persistent firstRun

if isempty(firstRun)
    firstRun = 1;

    dt = 0.1; % Sampling Time

    A = [1, dt;
         0, 1];

    H = [1, 0];

    Q = [1, 0;
         0, 3];
    
    R = 10;

    x_hat = [0, 20]'; % x_0(Initial state)
    P = 5 * eye(2); % P_0(Initial state)
end

xp = A * x_hat;
Pp = A*P*A' + Q;

K = Pp*H'*inv(H*Pp*H' + R);

x_hat = xp + K*(z - H*xp);
P = Pp - (K*H*Pp);

pos = x_hat(1);
vel = x_hat(2);