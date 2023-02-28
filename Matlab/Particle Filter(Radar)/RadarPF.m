function [pos, vel, alt] = RadarPF(z, dt)

persistent x  % 상태변수=[수평거리, 이동속도, 고도]'
persistent firstRun
persistent pt wt  % 파티클들의 위치와 가중치
persistent Npt  % 파티클의 갯수


if isempty(firstRun)
    x = [0, 90, 1100]';

    Npt = 1000;

    pt(1, :) = x(1) + 0.1*x(1) * randn(1, Npt);
    pt(2, :) = x(2) + 0.1*x(2) * randn(1, Npt);
    pt(3, :) = x(3) + 0.1*x(3) * randn(1, Npt);

    wt = ones(1, Npt) / Npt;

    firstRun = 1;
end

% I) 파티클 예측: 시스템 모델을 통해 각 파티클의 예측값을 구함
for k=1:Npt
    pt(:, k) = fx(pt(:, k), dt) + randn(3, 1);
end

% II) 파티클 가중치 갱신: 측정값과 각 파티클 예측 측정값의 차이를 기반으로 파티클의 가중치를 갱신
for k=1:Npt
    wt(k) = wt(k) * normpdf(z, hx(pt(:, k)), 10); % 가중치 변경
end
wt = wt / sum(wt);  % 가중치 정규화

% III) 추정값 계산: 각 파티클의 가중치를 고려한 가중합으로 추정값 계산
x = pt * wt';
pos = x(1);
vel = x(2);
alt = x(3);

% IV) 재샘플링 과정(Sequence Importance Resampling): 각 파티클의 가중치에 비례해 해당 파티클의 갯수를
% 조절
[pt, wt] = resampling(pt, wt, Npt);

%--------------------------
function xp = fx(x, dt)

A = eye(3) + dt * [0, 1, 0;
                   0, 0, 0;
                   0, 0, 0];
xp = A*x;
%--------------------------
function zp = hx(xhat)
x1 = xhat(1);
x3 = xhat(3);

zp = sqrt(x1^2 + x3^2);