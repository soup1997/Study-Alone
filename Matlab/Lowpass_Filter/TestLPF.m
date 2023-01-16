clear all;

Nsamples = 500;
Xsaved = zeros(Nsamples, 1);
Xmsaved = zeros(Nsamples, 1);
alpha = 0.9;

for k=1:Nsamples
    xm = GetSonar();
    x = LPF(xm, alpha);

    Xsaved(k) = x;
    Xmsaved(k) = xm;

end

dt = 0.02;
t = 0:dt:Nsamples*dt - dt;

figure(1)
hold on;
plot(t, Xmsaved, 'r.');
plot(t, Xsaved, 'b');
legend('Measured', 'LPF')