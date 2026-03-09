clc;
clear;
x = [1.2 1.5 1.7 2.0 2.4 2.6 3.1 3.3 3.5 3.9];
y = [10.247 10.541 10.815 11.089 11.357 11.621 11.896 12.164 12.430 12.708];
xx = 1.25;
% Используем polyfit для вычисления коэффициентов интерполяционного полинома
p = polyfit(x, y, length(x)-1);
% Используем polyval для вычисления значений интерполяционного полинома в точках xx
yy = polyval(p, xx);
plot(x,y,'o',xx,yy)
hold on;
plot(x,y,'k')
fprintf('Массив x: ');
for i = 1:length(x)
    fprintf('%g ', x(i));
end
fprintf('\n');
fprintf('Массив y: ');
for i = 1:length(y)
    fprintf('%g ', y(i));
end
fprintf('\n');
fprintf ('Значение по которому вычисляется интерполяция: %g\n', xx);
fprintf ("Ответ %.6f\n", yy);
