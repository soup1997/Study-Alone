dt = 0.001;
t = 0:dt:20;
steering_angle = deg2rad(2);
% steering_angle = deg2rad(3) * sin(2 * pi * 0.1 * t);

V = [20, 40]; % m/s

A = [2100, 1670, 0.99, 1.70, 61600, 52100]; % I, m, lf, lr, Cf, Cr
B = [850, 650, 1.63, 1.18, 70000, 90000]; % I, m, lf, lr, Cf, Cr
C = [3500, 1640, 1.30, 1.50, 50000, 80000]; % I, m, lf, lr, Cf, Cr

params = [A; B; C];
titles = ["A", "B", "C"];

for i=1:3
    Iz = params(i, 1);
    m = params(i, 2);
    lf = params(i, 3);
    lr = params(i, 4);
    Cf = params(i, 5);
    Cr = params(i, 6);
    
    figure(i);

    for Vx=V
        x = [0, 0, 0, 0]'; % y, y_dot, psi, psi_dot
        dx = [0, 0, 0, 0]'; % dx/dt
    
        A = [0, 1, 0, 0;
             0, -2*(Cf+Cr)/(m*Vx), 0, -Vx-(2*(Cf*lf - Cr*lr)/(m*Vx));
             0, 0, 0, 1;
             0, -2*(Cf*lf - Cr*lr)/Iz*Vx, 0, -2*(lf^2*Cf + lr^2*Cr)/(Iz*Vx)];
    
        B = [0, 2*Cf/m, 0, 2*lf*Cf/Iz]';
    
        X = zeros(length(t), 1);
        Y = zeros(length(t), 1);
    
        for j=1:length(t)

            dx = A*x + B.*steering_angle;
            x = dx .* dt;
        
            if j==1
                 X(j) = (Vx * cos(x(3))) * dt;
                 Y(j) = (Vx * sin(x(3))) * dt;
        
            else
                X(j) = X(j-1) + (Vx * cos(x(3))) * dt;
                Y(j) = Y(j-1) + (Vx * sin(x(3))) * dt;
            end
        
        end
        plot(X,Y);
        hold on;
    end
    
    xlabel("X");
    ylabel("Y");
    grid on;
    legend(int2str(V(1)), int2str(V(2)));
    title(titles(i));
end
