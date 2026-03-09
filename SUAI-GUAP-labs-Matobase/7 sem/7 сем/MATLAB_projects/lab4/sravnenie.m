% Пункт 6. Сравнение непрерывной и дискретной моделей

% Параметры системы
A = [2 3; 1 4];
init_cond = [1; 0];
tspan = [0 5];
t_continuous = linspace(tspan(1), tspan(2), 1000); % Вектор времени для точного решения

% 1. Точное решение (численное, через ode45)
[~, XY_cont] = ode45(@(t, xy) A * xy, t_continuous, init_cond);
x_cont = XY_cont(:, 1);
y_cont = XY_cont(:, 2);

% 2. Дискретное решение методом Эйлера с разными шагами
dt_values = [0.5, 0.1, 0.01]; % Шаги дискретизации

figure;

for i = 1:length(dt_values)
    dt = dt_values(i);
    t_discrete = tspan(1):dt:tspan(2); % Вектор времени для дискретного решения
    
    % Инициализация
    x_disc = zeros(size(t_discrete));
    y_disc = zeros(size(t_discrete));
    x_disc(1) = init_cond(1);
    y_disc(1) = init_cond(2);
    
    % Метод Эйлера
    for k = 1:length(t_discrete)-1
        dx_dt = 2*x_disc(k) + 3*y_disc(k);
        dy_dt = 1*x_disc(k) + 4*y_disc(k);
        
        x_disc(k+1) = x_disc(k) + dt * dx_dt;
        y_disc(k+1) = y_disc(k) + dt * dy_dt;
    end
    
    % Строим графики для x(t)
    subplot(2, 2, i);
    plot(t_continuous, x_cont, 'b-', 'LineWidth', 2, 'DisplayName', 'Непрерывная');
    hold on;
    plot(t_discrete, x_disc, 'ro--', 'MarkerSize', 4, 'DisplayName', ['Дискретная, \Delta t = ', num2str(dt)]);
    hold off;
    grid on;
    title(['Сравнение для x(t), \Delta t = ', num2str(dt)]);
    xlabel('Время t');
    ylabel('x(t)');
    legend;
    
    % Для y(t) на отдельном рисунке (по желанию)
%     subplot(2, 2, i+3);
%     plot(t_continuous, y_cont, 'r-', 'LineWidth', 2, 'DisplayName', 'Непрерывная');
%     hold on;
%     plot(t_discrete, y_disc, 'go--', 'MarkerSize', 4, 'DisplayName', ['Дискретная, \Delta t = ', num2str(dt)]);
%     hold off;
%     grid on;
%     title(['Сравнение для y(t), \Delta t = ', num2str(dt)]);
%     xlabel('Время t');
%     ylabel('y(t)');
%     legend;
end

% 3. Отдельный график для демонстрации неустойчивости при большом dt
dt_bad = 0.5;
t_bad = tspan(1):dt_bad:tspan(2);
x_bad = zeros(size(t_bad));
y_bad = zeros(size(t_bad));
x_bad(1) = init_cond(1);
y_bad(1) = init_cond(2);

for k = 1:length(t_bad)-1
    dx_dt = 2*x_bad(k) + 3*y_bad(k);
    dy_dt = 1*x_bad(k) + 4*y_bad(k);
    
    x_bad(k+1) = x_bad(k) + dt_bad * dx_dt;
    y_bad(k+1) = y_bad(k) + dt_bad * dy_dt;
end

figure;
plot(t_continuous, x_cont, 'b-', 'LineWidth', 2, 'DisplayName', 'Непрерывная');
hold on;
plot(t_bad, x_bad, 'ro--', 'LineWidth', 2, 'MarkerSize', 6, 'DisplayName', ['Дискретная, \Delta t = ', num2str(dt_bad)]);
hold off;
grid on;
title('Проявление неустойчивости метода Эйлера');
xlabel('Время t');
ylabel('x(t)');
legend;