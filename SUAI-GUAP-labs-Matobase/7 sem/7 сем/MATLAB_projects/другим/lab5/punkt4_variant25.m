% Пункт 4 — Вариант 25
% Фазовые траектории с управлением и без + вывод формулы регулятора
clear all; close all; clc;

% Параметры модели 
a       = 1;
lambda  = 1;
epsilon = 0.01;
alpha   = 0.4;
delta   = 0.12;                % берём самый интересный случай — был цикл

% Параметры синтезированного регулятора 
T  = 5;                        % постоянная времени апериодического звена (можно 3–10)
k  = 1/T;                      % коэффициент усиления (T⁻¹)

% Начальные условия (одинаковые для обеих траекторий)
x0 = [15; 12];
tspan = [0 200];

% 1. Без управления (uₛ = 0) 
[t1, x1] = ode45(@(t,x) model_no_control(t,x,a,lambda,epsilon,alpha,delta), tspan, x0);

% 2. С синтезированным управлением по указанию 
% ψ = x₂ – x₂₀,   f₂(x₁,x₂) = –λx₂ + x₁x₂/(1+αx₁) – δx₂²
% uₛ = –k ψ – f₂(x₁,x₂)
x20 = 8;   % желаемое количество хищников (можно менять: 4, 6, 8, 10…)
[t2, x2] = ode45(@(t,x) model_synthesized(t,x,a,lambda,epsilon,alpha,delta,x20,k), tspan, x0);

% Рисуем один фазовый портрет 
figure('Position',[200 200 900 750],'Color','w');
plot(x1(:,1), x1(:,2), 'b-', 'LineWidth', 2.8); hold on;
plot(x2(:,1), x2(:,2), 'r-', 'LineWidth', 3.2);
plot(x20*x20/lambda, x20, 'kp', 'MarkerSize', 18, 'MarkerFaceColor','k'); % примерная целевая точка

xlabel('x_1 (жертвы)', 'FontSize', 16);
ylabel('x_2 (хищники)', 'FontSize', 16);
title('Пункт 4. Фазовые траектории (вариант 25)', 'FontSize', 18, 'FontWeight','bold');

legend('без управления (лимитный цикл)', ...
       ['с управлением u_s = –T^{-1}ψ – f_2(x_1,x_2), T = ' num2str(T)], ...
       ['целевая точка x_{20} = ' num2str(x20)], ...
       'Location','best','FontSize',14);

grid on; box on; axis equal tight;
set(gca,'FontSize',14);

% Аналитическая формула регулятора 
disp(' ');
disp('Вывод формулы регулятора (по указанию):');
disp('ψ = x₂ – x_{20}');
disp('Требуем:  T ψ̇ + ψ = 0');
disp('ψ̇ = ẋ₂ = f₂(x₁,x₂) + uₛ');
disp('⇒ T(f₂(x₁,x₂) + uₛ) + (x₂ – x_{20}) = 0');
disp('⇒ uₛ = –T⁻¹ (x₂ – x_{20}) – f₂(x₁,x₂)');
disp(['f₂(x₁,x₂) = –λx₂ + x₁x₂/(1+αx₁) – δx₂²']);
disp(['⇒ uₛ = –(' num2str(k) ')(x₂ – ' num2str(x20) ') + λx₂ – x₁x₂/(1+' num2str(alpha) 'x₁) + ' num2str(delta) 'x₂²']);
disp(' ');

% Функции
function dxdt = model_no_control(~,x,a,lambda,epsilon,alpha,delta)
    x1 = x(1); x2 = x(2);
    dxdt = [a*x1 - x1*x2/(1+alpha*x1) - epsilon*x1^2;
            -lambda*x2 + x1*x2/(1+alpha*x1) - delta*x2^2];
end

function dxdt = model_synthesized(~,x,a,lambda,epsilon,alpha,delta,x20,k)
    x1 = x(1); x2 = x(2);
    f2 = -lambda*x2 + x1*x2/(1+alpha*x1) - delta*x2^2;
    us = -k*(x2 - x20) - f2;                    % точная формула из указания!
    dxdt = [a*x1 - x1*x2/(1+alpha*x1) - epsilon*x1^2;
            f2 + us];
end