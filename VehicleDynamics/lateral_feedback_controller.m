m = 1573;
Iz = 2873;
lf = 1.1;
lr = 1.58;
L = lf + lr;
Cf = 80000;
Cr = 80000;
Vx = 30;
 
dt = 0.001;
t = 0:dt:300;
R = zeros(length(t));
R(1:) = Inf;
R(length(t)/2:end) = 1000;

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


for i = t
    psi_des = Vx/R;
    dx = A*x;

end


