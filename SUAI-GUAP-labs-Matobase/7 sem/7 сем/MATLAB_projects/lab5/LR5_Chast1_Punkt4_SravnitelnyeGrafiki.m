% Пункт 4: Сравнительные графики для разных delta
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

% Сравнение x1(t)
figure(1);
hold on;
colors = {'b', 'g', 'r', 'k'};
legends = {};
for i = 1:length(deltas)
    delta = deltas(i);
    [t, x_sol] = ode45(@(t,x) baz_model(t,x,a,lambda,epsilon,alpha,delta), tspan, x0);
    plot(t, x_sol(:,1), colors{i}, 'LineWidth', 1.5);
    legends{i} = ['\delta = ' num2str(delta)];
end
xlabel('Время t');
ylabel('x1(t)');
title('Сравнение x1(t) для разных \delta');
legend(legends);
grid on;
% Описание: Для δ=0.12 — колебания; для остальных — сходимость к разным уровням.

% Сравнение фазовых портретов (subplot)
figure(2);
for i = 1:length(deltas)
    delta = deltas(i);
    [t, x_sol] = ode45(@(t,x) baz_model(t,x,a,lambda,epsilon,alpha,delta), tspan, x0);
    
    subplot(2,2,i);
    plot(x_sol(:,1), x_sol(:,2), colors{i}, 'LineWidth', 1.5);
    xlabel('x1');
    ylabel('x2');
    title(['Фазовый портрет, \delta = ' num2str(delta)]);
    grid on;
end
% Описание: Видна бифуркация — от цикла к спирали.