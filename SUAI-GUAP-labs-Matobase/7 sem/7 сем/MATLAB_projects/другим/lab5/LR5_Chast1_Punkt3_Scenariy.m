% Пункт 3 — Вариант 25
% Сценарий управления с целевой макропеременной ψ = x₂ – x₂₀ → 0
clear all; close all; clc;

% Параметры модели 
a       = 1;
lambda  = 1;
epsilon = 0.01;
alpha   = 0.4;

% Наши четыре значения δ
delta_values = [0.215, 0.221, 0.2395, 0.12];

% Задаём несколько желаемых уровней численности хищников
x20_values = [4, 6, 8, 10];

% Коэффициент усиления управления (чем больше — тем быстрее отрабатывает)
k = 30;                     

% Начальные условия
x0 = [1; 1];
tspan = [0 80];

% Цикл по δ и по x₂₀
for i = 1:4
    delta = delta_values(i);
    figure(i); clf;
    sgtitle(['Управление при \delta = ', num2str(delta)]);
    
    for j = 1:4
        x20 = x20_values(j);
        
        % Модель с управлением uₛ = –k·(x₂ – x₂₀)
        ode_fun = @(t,x) [ a*x(1) - (x(1)*x(2))/(1 + alpha*x(1)) - epsilon*x(1)^2 ; ...
                          -lambda*x(2) + (x(1)*x(2))/(1 + alpha*x(1)) - delta*x(2)^2 ...
                          - k*(x(2) - x20) ];
                      
        [t, sol] = ode45(ode_fun, tspan, x0);
        
        subplot(2,2,j)
        plot(t, sol(:,2), 'r-', 'LineWidth', 1.8); hold on;
        plot(t, x20*ones(size(t)), 'k--', 'LineWidth', 1.2);
        plot(t, sol(:,1), 'b-', 'LineWidth', 1.2);
        xlabel('Время t');
        ylabel('Популяции');
        title(['x_{20} = ', num2str(x20)]);
        legend('x_2(t)','Заданное x_{20}','x_1(t)','Location','best');
        grid on;
        ylim([0 max(15,max(sol(:,1)))]);
    end
end
