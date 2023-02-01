function xlpf = LPF(x, alpha)

persistent prevX;
persistent firstRun;

if isempty(firstRun)
    prevX = x;

    firstRun = 1;
end

xlpf = alpha * prevX + (1-alpha) * x;

prevX = xlpf;