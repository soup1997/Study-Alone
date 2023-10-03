dt = 0.001;
t = 0:dt:20;
steering_angle = deg2rad(2);

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
    l = lf + lr;
    Cf = params(i, 5);
    Cr = params(i, 6);
    mf = lr/l * m;
    mr = lf/l * m;

    for Vx=V
        Kv = (mf / 2*Cf) - (mr / 2*Cr);
        R = (l + Kv*Vx^2) / steering_angle;
        disp(R);
    end

end

%{
A: Kv > 0 (Understeer)
 1) V=20m/s, R=1.8902e+11
 2) V=40m/s , R=7.5610e+11

B: Kv < 0 (Oversteer)
 1) V=20m/s, R=-8.4955e+10
 2) V=40m/s, R=-3.3982e+11

C: Kv < 0 (Oversteer)
 1) V=20m/s, R=-9.7321e+10
 2) V=40m/s, R=-3.8928e+11
%}