function [z, posp, velp] = GetPos()

persistent Velp Posp

if isempty(Posp)
    Posp = 0;
    Velp = 80;
end

dt = 0.1;

w = 0 + 10 * randn(1); % 평균이 0이고 표준편차가 10인 RV생성(시스템 잡음)
v = 0 + 10 * randn(1); % 평균이 0이고 표준편차가 10인 RV생성(측정 잡음)

z = Posp + Velp*dt + v; % Mesurement with noise

Posp = z - v; % True Position
Velp = 80 + w; % True Speed

posp = Posp;
velp = Velp;