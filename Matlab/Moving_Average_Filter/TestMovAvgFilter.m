clear all

Nsamples = 500;
Xsaved = zeros(Nsamples,1);
Xmsaved = zeros(Nsamples, 1);

for k=1:Nsamples
    xm = GetSonar();
    x = MovAvgFilter(xm);

    Xsaved(k) = x;
    Xmsaved(k) = xm;
end

dt = 0.02;
t = 0:dt:Nsamples*dt - dt;

figure(1);
plot(t, Xmsaved, 'r.');
hold on;
plot(t, Xsaved, 'b');
legend('Measured', 'Moving Average Filter');
saveas(gcf, 'Moving Average Filter.png')