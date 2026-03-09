clear, clc
theta = 0:0.01:2*pi;
rho = sin(2*theta).*cos(2*theta);
[x,y] = pol2cart(theta,rho)
plot(x,y);
r=0.05;
phy=0:pi/180:2*pi;
 
x=r*cos(phy);
y=r*sin(phy);
 
hold on;
plot(x,y,'yellow');
 
