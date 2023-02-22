dt = 0.01;

Ki = 0.1^2;
Kp = sqrt(2) * 0.1;

num = [Kp, Ki];
den = [1, 0];

% 전달 함수를 이산식으로 변환
[numd, dend] = c2dm(num, den, dt, 'tustin');

%{
numd =

    0.1415   -0.1414


dend =

     1    -1
%}