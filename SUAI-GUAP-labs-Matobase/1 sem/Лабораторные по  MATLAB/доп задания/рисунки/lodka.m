clear, clc
theta = 0:0.01:2*pi;
rho = sin(2*theta).*cos(2*theta);
[x,y] = pol2cart(theta,rho)
plot(x,y);
r=0.05;
phy=0:pi/180:2*pi;
x1=r*cos(phy);
y1=r*sin(phy);
hold on;
plot(x1,y1,'yellow');
fill(x1,y1,'yellow');
v = [-0.0026 -0.049; 0.0026 -0.049; 0.0026 -0.7; -0.0026 -0.7];
f = [1 2 3 4];
patch('Faces',f,'Vertices',v,'FaceColor','green')

