clear; 
clc; 
close
% Ввод функции
f = @(x) exp(-(x.^2./2));
% Ввод параметров
A = 0;
B = 0.61;
tol = 0.001;
% Вычисление интеграла методом Симпсона с заданной точностью
n = 2;
s_old = 0;
s_new_pos = (B-A)*(f(A) + 4*f((A+B)/2) + f(B))/6;
s_new_neg = (B-A)*(-f(A) - 4*f((A+B)/2) - f(B))/6;
while abs((s_new_pos - s_old)/s_new_pos) > tol && n <= 1000000
    s_old = s_new_pos;
    n = n + 2;
    dx = (B-A)/n;
    s_new_pos = 0;
    s_new_neg = 0;
    for i = 0:2:n-2
        x1 = A + dx*i;
        x2 = A + dx*(i+2);
        s_new_pos = s_new_pos + (dx/3)*(f(x1)+4*f(x1+dx)+f(x2));
        s_new_neg = s_new_neg + (dx/3)*(-f(x1)-4*f(x1+dx)-f(x2));
    end
end
% Вычисление интеграла встроенной функцией integral для проверки
ss_pos = integral(f,A,B);
ss_neg = integral(@(x)(-f(x)),A,B);
% Вывод результатов
clc;
fprintf('Функция: exp.^(-(x.^2./2))');
fprintf('\nНижнее значение интеграла = %g\n', A);
fprintf('Верхнее значение интеграла = %.3f\n', B);
fprintf('Точность = %.3f\n', tol);
fprintf('Интеграл пользовательским методом = %.3f\n', s_new_pos);
fprintf('Интеграл встроенной функцией integral = %.3f\n', ss_pos);
cerror = ss_pos - s_new_pos;
k = -floor(log10(abs(cerror)));
cerror = floor(cerror*(10^k))/10^k;
fprintf('Погрешность интеграла = %.3f\n', cerror);
% Вывод графика функции 
xx = linspace(A,B,1000)';
yy = f(xx);
plot(xx,yy,'b');
hold on;
% Построение трапеции по границам интеграла
plot([A A], [0, f(A)], [B, B], [0, f(B)], 'Color', 'black');
% Закрашивание площади трапеции
area(xx, yy, 'FaceColor','blue', 'FaceAlpha', 0.2)
% Изменение подинтегральной функции на отрезках
n_parts = 70; % количество отрезков параболами
x_part = linspace(A,B,n_parts+1); % задание точек, в которых будут вершины парабол
y_part = f(x_part); % значения функции подинтегральной функции в вершинах парабол

% Разбиение на отрезки и построение кривых Безье
for i = 1:n_parts
    % Вычисление координат точек кривой Безье
    x0 = x_part(i);
    x1 = (x_part(i) + x_part(i+1))/2;
    x2 = x_part(i+1);
    y0 = y_part(i);
    y2 = y_part(i+1);
    y1 = y0 + 2/3*(y_part(i+1) - y_part(i))*(x1 - x0)/(x2 - x0); % Определение координаты y на точке x1
    
    % Построение кривой Безье
    t = linspace(0,1,100);
    x = (1-t).^2*x0 + 2*(1-t).*t*x1 + t.^2*x2;
    y = (1-t).^2*y0 + 2*(1-t).*t*y1 + t.^2*y2;
    
    % Отображение кривой Безье
    plot(x,y,'r');
end

% Настройка графика
title('Приближенная функция методом Симпсона');
xlabel('x');
ylabel('y')
legend('Функция','Левая граница','Правая граница','Закрашенная трапеция интеграла под функцией','Параболы соединенные кривыми Безье')
grid on;
% Добавление прямых осей x и y
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
ax.Box = 'off';