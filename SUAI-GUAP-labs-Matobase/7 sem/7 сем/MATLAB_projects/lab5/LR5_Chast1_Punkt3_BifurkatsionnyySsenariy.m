% Пункт 3: Бифуркационный сценарий для разных delta
clear all; close all; clc;

% Параметры модели
a = 1;
lambda = 1;
epsilon = 0.01;
alpha = 0.4;

% Значения delta (вариант 19)
deltas = [0.215, 0.221, 0.2395, 0.12];

% Начальные условия
x0 = [1; 1];

% Интервал времени
tspan = [0 200];

% Функция ODE
function dxdt = baz_model(t, x, a, lambda, epsilon, alpha, delta)
    x1 = x(1);
    x2 = x(2);
    dx1dt = a * x1 - (x1 * x2) / (1 + alpha * x1) - epsilon * x1^2;
    dx2dt = -lambda * x2 + (x1 * x2) / (1 + alpha * x1) - delta * x2^2;
    dxdt = [dx1dt; dx2dt];
end

% Цикл по delta
for i = 1:length(deltas)
    delta = deltas(i);
    [t, x_sol] = ode45(@(t,x) baz_model(t,x,a,lambda,epsilon,alpha,delta), tspan, x0);
    
    figure(i);
    subplot(2,1,1);
    plot(t, x_sol(:,1), 'b-', 'LineWidth', 1.5);
    hold on;
    plot(t, x_sol(:,2), 'r--', 'LineWidth', 1.5);
    xlabel('Время t');
    ylabel('x1, x2');
    title(['Зависимости x1(t), x2(t) для \delta = ' num2str(delta)]);
    legend('x1 (жертвы)', 'x2 (хищники)');
    grid on;
    
    subplot(2,1,2);
    plot(x_sol(:,1), x_sol(:,2), 'k-', 'LineWidth', 1.5);
    xlabel('x1');
    ylabel('x2');
    title(['Фазовый портрет для \delta = ' num2str(delta)]);
    grid on;
end

% Описания:
% δ=0.215: Сходится к x1≈79.90, x2≈6.62 (спираль к точке).
% δ=0.221: x1≈80.61, x2≈6.45 (спираль).
% δ=0.2395: x1≈82.48, x2≈5.96 (спираль).
% δ=0.12: Лимитный цикл (замкнутая петля, колебания).