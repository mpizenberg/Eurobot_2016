function [v] = vitesse(x,y,dt)
dx = x(2:end)-x(1:end-1);
dy = y(2:end)-y(1:end-1);
v = sqrt(dx.^2+dy.^2)/dt;
end