function [phi, theta, psi] = EulerEKF(z, rates, dt)

persistent H Q R
persistent x_hat P
persistent firstRun


if isempty(firstRun)
    % accelerometer can't measure yaw rate
    H = [1, 0, 0;
         0, 1, 0];
    
    % system noise
    Q = [0.0001, 0, 0;
         0, 0.0001, 0;
         0, 0, 0.1];
    
    % measurement noise
    R = [10, 0;
         0, 10];

    x_hat = [0, 0, 0]'; % initial state variable(roll=0, pitch=0, yaw=0)

    P = 10 * eye(3); % initial covariance

    firstRun = 1;
end

A = Ajacob(x_hat, rates, dt);

% step 1: Predict state & error covariance
xp = fx(x_hat, rates, dt);
Pp = A*P*A' + Q;

% step 2: Compute Kalman gain
K = Pp*H'*inv(H*Pp*H' + R);

% step 3: Compute the state estimate
x_hat = xp + K*(z - H*xp);

% step 4: Compute the error covariance
P = Pp - K*H*Pp;

phi = x_hat(1);
theta = x_hat(2);
psi = x_hat(3);

%------------------------
% function xp:
% Compute the angular velocity(p, q, r) to euler rate
% return predicted x
function xp = fx(xhat, rates, dt)

phi = xhat(1);
theta = xhat(2);

p = rates(1);
q = rates(2);
r = rates(3);

xdot = zeros(3, 1);
xdot(1) = p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta);
xdot(2) = q*cos(phi) - r*sin(phi);
xdot(3) = q*sin(phi)*sec(theta) + r*cos(phi)*sec(theta);

xp = xhat + xdot*dt; % cumulative sum

%------------------------
% function Ajacob:
% Compute the jacobian matrix of f(x)
% return A
function A = Ajacob(xhat, rates, dt)

A = zeros(3, 3);
phi = xhat(1);
theta = xhat(2);

p = rates(1);
q = rates(2);
r = rates(3);

A(1, 1) = q*cos(phi)*tan(theta) - r*sin(phi)*tan(theta);
A(1, 2) = q*sin(phi)*sec(theta)^2 + r*cos(phi)*sec(theta)^2;
A(1, 3) = 0;

A(2, 1) = -q*sin(phi) - r*cos(phi);
A(2, 2) = 0;
A(2, 3) = 0;

A(3, 1) = q*cos(phi)*sec(theta) - r*sin(phi)*sec(theta);
A(3, 2) = q*sin(phi)*sec(theta)*tan(theta) + r*cos(phi)*sec(theta)*tan(theta);
A(3, 3) = 0;

A = eye(3) + A*dt;