function avg = MovAvgFilter(x)

persistent n xbuf
persistent firstRun

if isempty(firstRun)
    n = 10; % 10개의 데이터에 대한 평균을 구함
    xbuf = x * ones(n, 1); % 이동평균 필터 적용을 위한 buffer 생성
    firstRun = 1;
end


% Queue의 FIFO 특성을 이용하여 구현하는게 더 간편함
for m=1:n-1
    xbuf(m) = xbuf(m+1); % 데이터 앞으로 옮기기
end

xbuf(n) = x; % 현재 스텝에 입력된 데이터


avg = sum(xbuf) / n;
