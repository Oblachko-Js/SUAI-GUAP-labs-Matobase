% Пункт 3 и 4 — Вариант 25
% Сравнение неуправляемой и управляемой модели
% Управление только во втором уравнении: u_s = –k·(x₂ – x₂₀)
clear all; close all; clc;

% Наши параметры 
a       = 1;
lambda  = 1;
epsilon = 0.01;
alpha   = 0.4;

% Выбираем δ = 0.12 — самый интересный случай (без управления — цикл)
delta = 0.12;

% Желаемый уровень хищников (можно менять: 4, 6, 8, 10…)
x20 = 8;

% Коэффициент усиления управления (чем больше — тем быстрее отрабатывает)
k = 40;                    

% Момент включения управления
t_switch = 60;

% Начальные условия
x0 = [10; 12];
tspan = [0 150];

% Интегрируем 
[t, x] = ode45(@(t,x) model_with_switch(t,x,a,lambda,epsilon,alpha,delta,x20,k,t_switch), ...
               tspan, x0, odeset('RelTol',1e-10));

% Графики 
figure(1);
plot(t, x(:,1), 'b-',  'LineWidth',2); hold on;
plot(t, x(:,2), 'r-',  'LineWidth',2);
plot([t_switch t_switch], [0 max(x(:,1))+5], 'k:', 'LineWidth',2);
xlabel('Время t'); ylabel('Численность популяций');
title('Сравнение: синий — жертвы x_1(t), красный — хищники x_2(t)');
legend('x_1(t)','x_2(t)','включение управления','Location','best');
grid on; box on;

figure(2);
% До включения управления — синий
idx1 = t <= t_switch;
plot(x(idx1,1), x(idx1,2), 'b-', 'LineWidth',2.5); hold on;
% После включения — красный
idx2 = t > t_switch;
plot(x(idx2,1), x(idx2,2), 'r-', 'LineWidth',3);
plot(x20*x20/lambda, x20, 'kp', 'MarkerSize',15, 'MarkerFaceColor','k'); 
xlabel('x_1 (жертвы)'); ylabel('x_2 (хищники)');
title('Фазовый портрет: синий — без управления, красный — с управлением');
legend('неуправляемая траектория','управляемая траектория','целевая линия x_2 = x_{20}','Location','best');
grid on; box on;

figure(3);
u = zeros(size(t));
u(t >= t_switch) = -k * (x(t >= t_switch,2) - x20);
plot(t, u, 'g', 'LineWidth',2.2);
xlabel('Время t'); ylabel('Управляющее воздействие u_s');
title(['Сигнал управления u_s = –k·(x_2 – ', num2str(x20), ')   k = ', num2str(k)]);
grid on; box on;

% Функция системы с переключением управления 
function dxdt = model_with_switch(t,x,a,lambda,epsilon,alpha,delta,x20,k,t_switch)
    x1 = x(1); x2 = x(2);
    
    % Неуправляемая часть (всегда)
    dx1 = a*x1 - (x1*x2)/(1 + alpha*x1) - epsilon*x1^2;
    dx2 = -lambda*x2 + (x1*x2)/(1 + alpha*x1) - delta*x2^2;
    
    % Управление только во втором уравнении
    if t >= t_switch
        us = -k * (x2 - x20);
    else
        us = 0;
    end
    
    dxdt = [dx1; dx2 + us];
end