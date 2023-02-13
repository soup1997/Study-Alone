function [Xi, W] = SigmaPoints(xm, P, kappa)

n = numel(xm); % 배열에 포함된 요소의 갯수 반환
Xi = zeros(n, 2*n+1); % simga points = Xi의 열
W = zeros(2*n+1, 1);

Xi(:, 1) = xm;
W(1) = kappa / (n+kappa);

U = chol((n+kappa)*P);

for k=1:n
    Xi(:, k+1) = xm + U(k, :)';
    W(k+1) = 1 / (2 * (n+kappa));
end

for k=1:n
    Xi(:, n+k+1) = xm - U(k, :)';
    W(n+k+1) = 1 / (2 * (n+kappa));
end