function [phi, theta, psi] = EulerAccel(ax, ay, az)

phi = atan(ay / sqrt(ax^2  + az^2));
theta = atan(ax / sqrt(ay^2 + az^2));
psi = atan(sqrt(ax^2 + ay^2) / az);