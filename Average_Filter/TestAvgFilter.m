clear;

% 0.2초 마다 전압의 평균을 재는 예제%

dt = 0.2;
t = 0:dt:10; % 0초부터 10초까지 0.2초간격

Nsamples = length(t);
AvgSaved = zeros(Nsamples, 1); % 평균을 저장할 배열
Xmsaved = zeros(Nsamples, 1); % 새로운 데이터 값을 저장할 배열 

for k=1:Nsamples
    xm = GetVolt(); % 전압 값 생성
    avg = AvgFilter(xm); % 평균 구하기 

    AvgSaved(k) = avg;
    Xmsaved(k) = xm;
end

figure(1);
plot(t, Xmsaved, 'r:*');
hold on;
plot(t, AvgSaved, 'o-');
legend('Measured', 'Average');
saveas(gcf, 'Average Filter.png')
