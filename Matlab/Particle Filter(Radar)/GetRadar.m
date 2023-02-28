function r = GetRadar(dt)

persistent posp % 이전 위치를 저장할 변수

if isempty(posp)
    posp = 0;
end

vel = 100 + 5*randn(1);
alt = 1000 + 10*randn(1);

pos = posp + vel*dt;
v = 0 + pos*0.05*randn(1); % Measurement noise

r = sqrt(pos^2 + alt^2) + v;

posp = pos;
end