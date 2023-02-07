function [phi, theta, psi] = EulerGyro(p, q, r, dt)
persistent prevPhi prevTheta prevPsi

if isempty(prevPhi)
    prevPhi = 0;
    prevTheta = 0;
    prevPsi = 0;
end

rotationMat = [1, sin(prevPhi)*tan(prevTheta), cos(prevPhi)*tan(prevTheta)
               0, cos(prevPhi), -sin(prevPhi) 
               0, sin(prevPhi)/cos(prevTheta), cos(prevPhi)/cos(prevTheta)];

angle = dt * rotationMat * [p, q, r]';

phi = prevPhi + angle(1);
theta = prevTheta + angle(2);
psi = prevPsi + angle(3);

prevPhi = phi;
prevTheta = theta;
prevPsi = psi;