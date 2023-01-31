function [xh, yh] = TrackKalman(xm, ym)

persistent A H Q R
persistent x_hat P
persistent firstRun

if isempty(firstRun)
    dt = 1; % 1 Hz
    
    %{
    posx_(k+1) = (posx + velx * dt)
    posy_(k+1) = (posy + vely * dt)
    %}
    A = [1, dt, 0, 0
         0, 1, 0, 0
         0, 0, 1, dt
         0, 0, 0, 1];

    H = [1, 0, 0, 0
         0, 0, 1, 0];

    Q = 1.0 * eye(4);
    R = 50.0 * eye(2);
    
    %{
    x_hat = [pos_x
             vel_x
             pos_y
             vel_y]
    %}
    x_hat = [0, 0, 0, 0]'; 
    P = 100 * eye(4);

    firstRun = 1;
end

xp = A*x_hat;
Pp = A*P*A' + Q;
K = Pp*H' * inv(H*Pp*H' + R);

z = [xm, ym]';
x_hat = xp + K*(z - H*xp);
P = Pp - K*H*Pp;

% 추정 위치 반환
xh = x_hat(1);
yh = x_hat(3);

