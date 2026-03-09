% Пункт 2: Фазовые портреты с разной точностью
clear all; close all; clc;

% Параметры модели
a = 1;
lambda = 1;
epsilon = 0.01;
alpha = 0.4;
delta_phase = 0.12;  % Для демонстрации лимитного цикла

% Начальные условия
x0 = [1; 1];

% Интервал времени (длинный для цикла)
tspan_long = [0 1000];

% Функция ODE
function dxdt = baz_model(t, x, a, lambda, epsilon, alpha, delta)
    x1 = x(1);
    x2 = x(2);
    dx1dt = a * x1 - (x1 * x2) / (1 + alpha * x1) - epsilon * x1^2;
    dx2dt = -lambda * x2 + (x1 * x2) / (1 + alpha * x1) - delta * x2^2;
    dxdt = [dx1dt; dx2dt];
end

% Низкая точность: RelTol=1e-2 (~2 знака)
opts_low = odeset('RelTol',1e-2, 'AbsTol',1e-4);
[t_low, x_low] = ode45(@(t,x) baz_model(t,x,a,lambda,epsilon,alpha,delta_phase), tspan_long, x0, opts_low);

figure(1);
plot(x_low(:,1), x_low(:,2), 'b-', 'LineWidth', 1.5);
xlabel('x1');
ylabel('x2');
title('Фазовый портрет с низкой точностью (RelTol=1e-2)');
grid on;
% Описание: Искажение, траектория уходит в отрицательные значения из-за ошибок.

% Высокая точность: RelTol=1e-15 (~15 знаков)
opts_high = odeset('RelTol',1e-15, 'AbsTol',1e-15);
[t_high, x_high] = ode45(@(t,x) baz_model(t,x,a,lambda,epsilon,alpha,delta_phase), tspan_long, x0, opts_high);

figure(2);
plot(x_high(:,1), x_high(:,2), 'r-', 'LineWidth', 1.5);
xlabel('x1');
ylabel('x2');
title('Фазовый портрет с высокой точностью (RelTol=1e-15)');
grid on;
% Описание: Замкнутая петля (лимитный цикл), стабильные осцилляции.