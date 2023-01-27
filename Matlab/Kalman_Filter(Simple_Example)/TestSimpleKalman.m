clear all

dt = 0.2; % Sampling Time
t = 0:dt:10; % Simulation Time

Nsamples = length(t);

Xsaved = zeros(Nsamples, 3);
Zsaved = zeros(Nsamples, 1);

plot_title = ["Kalman Filter", "Measurements", "P(Error Covariance)", "Kalman Gain"];

for k=1:Nsamples
    z = GetVolt();
    [volt, Cov, Kg] = SimpleKalman(z);

    Xsaved(k, :) = [volt, Cov, Kg]; % 여려변수를 한번에 대입
    Zsaved(k) = z;

end

for i=1:3
    subplot(3, 1, i)
    xlabel('Time [sec]')
    
    if i == 1
        plot(t, Xsaved(:, 1), 'o-'); % Estimated Voltage
        hold on;
        plot(t, Zsaved, 'r:*'); % Raw Voltage
        legend(plot_title(1), plot_title(2));

    elseif i == 2
        plot(t, Xsaved(:, 2), 'o-'); % Error Covariance(P)
        ylabel('P')
        title(plot_title(i+1))
    
    elseif i == 3
        plot(t, Xsaved(:, 3), 'o-'); % Kalman Gain
        ylabel('K')
        title(plot_title(i+1))
    end
    grid on;
end

saveas(gcf, "Simple Kalman Filter Example.png")