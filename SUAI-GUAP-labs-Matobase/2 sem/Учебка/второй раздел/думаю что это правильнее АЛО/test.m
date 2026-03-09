clc;
clear;
% Задаем переменную для описания ввода массивов
description = "Введите";
% Ввод значений массива x и y
x_str = strrep(input(description + " значения массива x, разделяя их пробелами: ",'s'), ',', '.');
while true
    x_cell = strsplit(x_str, ' ');
    x = str2double(x_cell);
    if any(isnan(x)) || length(x) < 2 || length(unique(x)) ~= length(x)
        disp("Массив x должен содержать не менее двух уникальных чисел, разделенных пробелами.");
        x_str = strrep(input("Введите значения массива x: ", 's'), ',', '.');
        continue
    end
    break
end

y_str = strrep(input(description + " значения массива y, разделяя их пробелами: ",'s'), ',', '.');
while true
    y_cell = strsplit(y_str, ' ');
    y = str2double(y_cell);
    if any(isnan(y)) || length(y) ~= length(x)
        disp("Массив y должен содержать столько же чисел, сколько и массив x, разделенных пробелами.");
        y_str = strrep(input("Введите значения массива y: ", 's'), ',', '.');
        continue
    end
    break
end
% Вычисляем разделенные разности
n = length(x);
F = y'; % инициализация матрицы разделенных разностей
for j = 2:n
for i = 1:n-j+1
F(i,j) = (F(i+1,j-1) - F(i,j-1))/(x(i+j-1) - x(i));
end
end
% Ввод значения xx
xx_str = strrep(input("Введите значения xx, разделяя их пробелами или запятыми и используя точку для разделения дробной части: ", 's'), ',', '.');
while true
    xx_cell = strsplit(xx_str, {' ', ','});
    xx = str2double(xx_cell);
    if any(isnan(xx))
        disp("xx должно быть числом, в числе должен быть один разделитель.");
        xx_str = strrep(input("Введите значения xx: ", 's'), ',', '.');
        continue
    end
    break
end
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
% Вывод результата
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
% Добавление прямых осей x и y
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
ax.Box = 'off';