m = 1573;
Iz = 2873;
lf = 1.1;
lr = 1.58;
L = lf + lr;
Cf = 80000;
Cr = 80000;
Vx = 30;
 
dt = 0.01;
t = 0:dt:300;
R = zeros(length(t));
R(1:100) = Inf; % from 0 to 10 sec (straight, radius=inf)
R(100:end) = 1000; % from 10 sec to 300 sec (circle, radius=1000)

x = [0, 0, 0, 0]'; % e1, e1_dot, e2, e2_dot

A = [0, 1, 0, 0;
     0, (2*Cf+2*Cr)/-m*Vx, (2*Cf+2*Cr)/m, (-2*Cf*lf+2*Cr*lr)/m*Vx;
     0, 0, 0, 1;
     0, (2*Cf*lf-2*Cr*lr)/-Iz*Vx, (2*Cf*lf-2*Cr*lr)/Iz, (2*Cf*lf^2+2*Cr*lr^2)/-Iz*Vx];

B1 = [0;
      2*Ca/m;
      0;
      2*Ca*lf/Iz];

B2 = [0;
      ((2*Cf*lf - 2*Cr*lr)/-m*Vx) - Vx;
      0;
      (2*Cf*lf^2 + 2*Cr*lr^2)/-Iz*Vx];


for radius = R
    psi_des = Vx/R;
    steering_angle = L/R + ((mf/(2*Cf))-(mr/(2*Cr)) * (Vx^2/R));
    dx = (A*x) + (B1.*steering_angle) + (B2 .*psi_des);
    x = dx * dt;
end
