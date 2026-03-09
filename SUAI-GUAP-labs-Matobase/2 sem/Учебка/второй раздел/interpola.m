function [yy,xx,y] = interpola(xx, y, x)
n = length(x);
% Вычисление интерполяционного полинома методом Ньютона
yy = y(1);
for i = 2:n
    p = 1;
    for j = 1:i-1
        p = p * (xx - x(j));
    end
    yy = yy + y(i) * p;
end
end
