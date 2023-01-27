function [volt, Px, K] = SimpleKalman(z)

%{
System Model

x_(k+1) = x_k (배터리의 전압이 일정하게 유지되므로 이전상태와 현재상태가 동일)
z_k = x_k + v_k (Measurement Value = State Variable + Measurement Noise)

x_0 = 14 (Initial State Value = 14)
v_k ~ N(0, 4) (Normal Distribution, mean = 0, variance = 4)

%}

persistent A H Q R
persistent x_hat P
persistent firstRun

if isempty(firstRun)
    A = 1;
    H = 1;

    Q = 0; % w_k(시스템 잡음)의 공분산 행렬(Diagonal Matrix)
    R = 4; % v_k(센서 측정 잡음)의 공분산 행렬(Diagonal Matrix)

    x_hat = 14; % x_0(Initial Value)
    P = 6; % P_0 (Initial Error Covariance)

    firstRun = 1;

end

% Prediction
x_pred = A * x_hat;
P_pred = A*P*A' + Q;

% Calculate Kalman Gain
K = (P_pred*H')/(H*P_pred*H' + R);

% Update
x_hat = x_pred + K*(z - H*x_pred);
P = P_pred - K*H*P_pred;

% return Estimated State Value & Error Covariance
volt = x_hat;
Px = P;

end
