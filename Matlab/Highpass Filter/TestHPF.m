clear all;

Nsamples = 500;
Xsaved = zeros(Nsamples, 1);
Xmsaved = zeros(Nsamples, 1);

for k=1:Nsamples
    zm = GetSonar();
    x = HPF(zm);

    Xsaved(k) = x;
    Xmsaved(k) = zm;
end

dt = 0.02;
t = 0:dt:Nsamples*dt-dt;

figure(1);
hold on;
plot(t, Xmsaved, 'r.');
plot(t, Xsaved, 'b');
legend('Measured', 'HPF');
saveas(gcf, 'Highpass Filter.png');

figure(2);
hold on;
plot(t, Xmsaved, 'r.');
plot(t, Xmsaved - Xsaved, 'b');
legend('Mesured', 'Measured-HPF');
saveas(gcf, 'Highpass Filter2.png');