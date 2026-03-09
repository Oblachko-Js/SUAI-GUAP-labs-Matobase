function plot_polynomial(x, y, xx, yy)
% Строим график полинома, проходящего через заданные точки и точки, добавленные пользователем

F = calculate_divided_differences(x, y);

[x_range, y_range] = evaluate_polynomial_range(F, x, xx);
hold on;
plot(x,y,'o','color','b','DisplayName','Набор точек');
plot(xx,yy,'o','color','r','DisplayName','Точки интерполяции');
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
F_new = calculate_new_divided_differences(x_new, y_new);

% Интерполируем полином на интервале от минимального значения x до максимального значения xx
[x_range_new, y_range_new] = evaluate_new_polynomial_range(F_new, x_new);

% Обновляем график
plot(x_range_new,y_range_new,'color','k','DisplayName','Полином');
legend();
% Добавление прямых осей x и y
ax = gca;
ax.XAxisLocation = 'origin';
ax.YAxisLocation = 'origin';
ax.Box = 'off';
end