A = [2100, 1670, 0.99, 1.70, 61600, 52100]; % I, m, lf, lr, Cf, Cr
B = [850, 650, 1.63, 1.18, 70000, 90000]; % I, m, lf, lr, Cf, Cr
C = [3500, 1640, 1.30, 1.50, 50000, 80000]; % I, m, lf, lr, Cf, Cr
params = [A; B; C];
titles = ["A", "B", "C"];
V = [20, 40]; % m/s

for i=1:3
    Iz = params(i, 1);
    m = params(i, 2);
    lf = params(i, 3);
    lr = params(i, 4);
    l = lf + lr;
    Cf = params(i, 5);
    Cr = params(i, 6);
    
    figure(i);

    for Vx=V
        D = (2*m*(lf^2*Cf + lr^2*Cr) + 2*Iz*(Cf + Cr))/ (m*Iz*Vx);
        S = ((4*Cf*Cr*l^2) / (m*Iz*Vx^2)) + (2*(lr*Cr-lf*Cf)/Iz);
        c = [1, D, S];
        r = roots(c);
        disp(r);

        real_r = real(r);
        imag_r = imag(r);

        plot(real_r, imag_r, 'o');
        hold on;
    end

    xlabel("Real");
    ylabel("Imag");
    grid on;
    legend(int2str(V(1)), int2str(V(2)), 'Location','north');
    title(titles(i));
end
