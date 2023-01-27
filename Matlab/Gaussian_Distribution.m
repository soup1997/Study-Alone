% Normal Distribution(Gaussian Distribution)

mu = 0;
sigma = 0.7;

x = -2:0.01:2;

gaussian_pdf = (1 / (sigma * sqrt(2 * pi))) * exp(-1/2 .* ((x - mu)/ sigma).^2);


plot(x, gaussian_pdf);
