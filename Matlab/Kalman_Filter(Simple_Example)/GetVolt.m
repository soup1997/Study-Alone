function z_k = GetVolt()

v_k = 0 + 4 * randn(1, 1); % Measurement Noise
z_k = 14.4 + v_k; % Measurement Value

end