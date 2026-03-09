clc;
clear;
% Ввод значений массива x и y
x = [1.2 1.5 1.7 2.0 2.4 2.6 3.1 3.3 3.5 3.9];
y = [10.247 10.541 10.815 11.089 11.357 11.621 11.896 12.164 12.430 12.708];
% Вычисляем разделенные разности
n = length(x);
F = y'; % инициализация матрицы разделенных разностей
for j = 2:n
for i = 1:n-j+1
F(i,j) = (F(i+1,j-1) - F(i,j-1))/(x(i+j-1) - x(i));
end
end
xx = [1.25 3.25];
% Вычисление значения полинома для всех заданных точек
yy = zeros(size(xx));
for k = 1:length(xx)
xk = xx(k);
Pk = F(1,1);
for j=2:n
prod = 1;
for i=1:j-1
prod = prod * (xk - x(i));
end
Pk = Pk + F(1,j)*prod;
end
yy(k) = Pk;
end
% Строим график полинома, проходящего через заданные точки и точки, добавленные пользователем
x_range = linspace(min([x xx]), max([x xx]), 100);
y_range = zeros(size(x_range));
for i=1:length(x_range)
P = F(1,1);
for j=2:n
prod = 1;
for k=1:j-1
prod = prod * (x_range(i) - x(k));
end
P = P + F(1,j)*prod;
end
y_range(i) = P;
end
hold on;
plot(x,y,'o','color','b','DisplayName','Набор точек');
plot(xx,yy,'o','color','r','DisplayName','Точка интерполяции');
xlabel('x');
ylabel('y');
title('Полином');
xlim([min(x_range), max(x_range)]);
ylim([min(y_range), max(y_range)]);
axis tight;
box on;
legend();
% Вычисляем новые разделенные разности
x_new = [x xx];
y_new = [y yy];
n_new = length(x_new);
F_new = zeros(n_new);
F_new(:,1) = y_new'; % инициализация матрицы разделенных разностей
for j = 2:n_new
for i = 1:n_new-j+1
F_new(i,j) = (F_new(i+1,j-1) - F_new(i,j-1))/(x_new(i+j-1) - x_new(i));
end
end
% Интерполируем полином на интервале от минимального значения x до максимального значения xx
x_range_new = linspace(min(x_new), max(x_new), 100);
y_range_new = zeros(size(x_range_new));
for i=1:length(x_range_new)
P = F_new(1,1);
for j=2:n_new
prod = 1;
for k=1:j-1
prod = prod * (x_range_new(i) - x_new(k));
end
P = P + F_new(1,j)*prod;
end
y_range_new(i) = P;
end
% Обновляем график
plot(x_range_new,y_range_new,'color','k','DisplayName','Полином');
legend();
% Вывод результата
% Используем polyfit для вычисления коэффициентов интерполяционного полинома
p = polyfit(x, y, length(x)-1);
% Используем polyval для вычисления значений интерполяционного полинома в точках xx
pp = polyval(p, xx);
fprintf("Таблица значений x и y:\n");
fprintf("  x         y   \n");
for i = 1:length(x)
    fprintf("%.6f   %.6f\n", x(i), y(i));
end
fprintf("\n");
fprintf("Значения полинома в точках:\n");
fprintf("  xx         yy        yy(Matlab)  \n");
for i = 1:length(xx)
    fprintf("%.6f   %.6f   %.6f\n", xx(i), yy(i),pp(i));
end
fprintf("\n");
% Добавление прямых осей x и y
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
ax.Box = 'off';