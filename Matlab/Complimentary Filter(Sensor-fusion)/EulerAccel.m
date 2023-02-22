function [phi, theta] = EulerAccel(ax, ay, az)

phi = atan(ay / az);
theta = atan(ax / sqrt(ay^2 + az^2));