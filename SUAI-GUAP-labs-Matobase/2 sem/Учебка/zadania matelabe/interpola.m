function [yy,xx,y] = interpola(xx, y, x)
n = length(x); % определение переменной n
% Вычисление интерполяционного полинома методом Ньютона
yy = y(n);
for i = n-1:-1:1
yy = y(i) + (xx - x(i))*yy;
end
end