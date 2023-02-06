function [pos, vel, alt] = RadarEKF(z, dt)

persistent A Q R
persistent x_hat P
persistent firstRun


if isempty(firstRun)
    A = eye(3) + dt * [0,1,0;
                       0,0,0;
                       0,0,0];
    Q = [0,0,0;
         0, 0.001, 0;
         0, 0, 0.001]; % w_k의 공분산 행렬

    R = 10; % v_k의 공분산 행렬

    x_hat = [0, 90, 1100]'; % 임의로 예측한 초기 추정값
    P = 10 * eye(3);

    firstRun = 1;
end

H = Hjacob(x_hat); % 시스템 행렬의 야코비안 H 계산
xp = A * x_hat;
Pp = A*P*A' + Q;

K = Pp*H'*inv(H*Pp*H' + R);

x_hat = xp + K*(z-hx(xp));
P = Pp - K*H*Pp;

pos = x_hat(1);
vel = x_hat(2);
alt = x_hat(3);

end

%------------------------

function zp = hx(xhat)

x1 = xhat(1);
x3 = xhat(3);

zp = sqrt(x1^2 + x3^2);

end

%------------------------

function H = Hjacob(xp)

H = zeros(1, 3);

x1 = xp(1);
x3 = xp(3);

H(1) = x1 / sqrt(x1^2 + x3^2);
H(2) = 0;
H(3) = x3 / sqrt(x1^2 + x3^2);

end