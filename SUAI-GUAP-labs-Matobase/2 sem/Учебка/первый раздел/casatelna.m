function casatelna(fx, x0, f_x_vals, f_y_vals, dfx)
% Вычисление уравнения касательной к корню
    y_tan = fx + dfx*(f_x_vals-x0);
    % Касательная
    plot(f_x_vals, y_tan, 'y', 'LineWidth', 1.5);
    % Добавление графика оси x
    plot([max(f_x_vals(1),-10), min(f_x_vals(end),10)], [0, 0], 'k', 'LineWidth', 1);
    % Добавление графика оси y
    plot([0, 0], [min(min(f_y_vals)-2,-10), max(max(f_y_vals)+2,10)], 'k', 'LineWidth', 1);
    % Установка меток на осях
    xlabel('x');
    ylabel('y');
    title('График функции');
    grid on;
    hold on;