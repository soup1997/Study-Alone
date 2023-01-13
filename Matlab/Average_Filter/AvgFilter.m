%{
persistent는 C언어의 Static(정적 변수)와 같은 역할
%}

function avg = AvgFilter(x)

persistent prevAvg k
persistent firstRun % Flag 변수

if isempty(firstRun) % 함수 초기화
    k = 1;
    prevAvg = 0;

    firstRun = 1;
end

alpha = (k-1)/ k;
avg = alpha * prevAvg + (1-alpha) * x;

prevAvg = avg;
k = k + 1; % 매 스텝마다 k값 1씩 증가
