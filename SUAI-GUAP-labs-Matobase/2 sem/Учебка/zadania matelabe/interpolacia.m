clc;
clear;

% Входные данные
x = [1.2 1.5 1.7 2.0 2.4 2.6 3.1 3.3 3.5 3.9];
y = [9.277, 9.542, 9.812, 10.084, 10.358, 10.626, 10.890, 11.162, 11.431, 11.704];

% Запросить значение xx от пользователя
xx_str = input(sprintf('Введите значение xx из списка [%s]: ', num2str(x)), 's');
while true
    % Преобразовать xx_str в число и проверить его наличие в x
    xx = str2double(xx_str);
    if ~isnan(xx) && ismember(xx, x)
        break
    end
    
    % Сообщить об ошибке и запросить новое значение
    fprintf('Некорректное значение. Введите число из списка [%s].\n', num2str(x));
    xx_str = input(sprintf('Введите значение xx из списка [%s]: ', num2str(x)), 's');
end

% Вычисляем интерполяционный многочлен в форме Ньютона
Pn = y(1);
for j = 2:length(y)
    product = 1;
    for i = 1:j-1
        product = product * (xx - x(i));
    end
    Pn = Pn + f(j,j) * product;
end

fprintf("Ответ %.6f\n", Pn);

% Визуализация
xx_points = linspace(min(x), max(x), 100);
yy_points = zeros(size(xx_points));
for i = 1:length(xx_points)
    yy_points(i) = interp_Newton(x, y, xx_points(i), f);
end
plot(xx_points, yy_points, 'b-', x, y, 'ro', xx, Pn, 'go');
legend('интерполяционный многочлен', 'узлы интерполяции', 'значение в точке xx');
xlabel('x');
ylabel('y');
title('Интерполяция методом Ньютона');
