function [phi, theta, psi] = EulerKalman(A, z)

persistent H Q R
persistent x_hat P
persistent firstRun

if isempty(firstRun)
    H = eye(4);
   
    % Initial Noise
    Q = 0.0001 * eye(4);
    R = 10 * eye(4); 

    % Initial Value
    x_hat = [1, 0, 0, 0]';
    P = eye(4);

    firstRun = 1;
end

xp = A * x_hat;
Pp = A*P*A' + Q;

K = Pp*H'*inv(H*Pp*H' + R);

x_hat = xp + K*(z - H*xp);
P = Pp - K*H*Pp;

% Quaternion to Euler
phi = atan2(2*(x_hat(3)*x_hat(4) + x_hat(1)*x_hat(2)), 1 -2*(x_hat(2)^2 + x_hat(3)&2));
theta = -asin(2*(x_hat(2)*x_hat(4) - x_hat(1)*x_hat(3)));
psi = atan2(2*(x_hat(2)*x_hat(3) + x_hat(1)*x_hat(4)), 1 - 2*(x_hat(3)^2+x_hat(4)^2));