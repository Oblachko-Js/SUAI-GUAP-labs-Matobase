clear all; close all; clc;

% Параметры варианта 25
a       = 1;
lambda  = 1;        
epsilon = 0.01;
alpha   = 0.4;      
delta_values = [0.215, 0.221, 0.2395, 0.12];

x0    = [1; 1];
tspan = [0 500];

% Система уравнений (u = 0)
f = @(t,x,delta) [ a*x(1) - (x(1)*x(2))/(1 + alpha*x(1)) - epsilon*x(1)^2 ; ...
                  -lambda*x(2) + (x(1)*x(2))/(1 + alpha*x(1)) - delta*x(2)^2 ];

%% Пункт 1 — временные зависимости x₁(t), x₂(t)
figure('Position',[100 100 1200 800]);
for k = 1:4
    [t,x] = ode45(@(t,x) f(t,x,delta_values(k)), tspan, x0, ...
                  odeset('RelTol',1e-10,'AbsTol',1e-10));
    
    subplot(4,2,2*k-1)
    plot(t,x(:,1),'b','LineWidth',1.4); hold on
    plot(t,x(:,2),'r','LineWidth',1.4)
    title(['δ = ' num2str(delta_values(k))])
    ylabel('Популяции')
    legend('x_1(t) — жертвы','x_2(t) — хищники')
    grid on
    xlabel('t')
end
sgtitle('Пункт 1. Зависимости x_1(t), x_2(t) при разных δ (u = 0)');

%% Пункт 2 — фазовые портреты с разной точностью (δ = 0.12)
delta_phase = 0.12;
tspan_long = [0 800];

% Низкая точность
[t1,x1] = ode45(@(t,x) f(t,x,delta_phase), tspan_long, x0, ...
                odeset('RelTol',1e-2,'AbsTol',1e-4));
figure
plot(x1(:,1),x1(:,2),'b-','LineWidth',1.8)
title('Фазовый портрет с низкой точностью (RelTol=1e-2), δ = 0.12')
xlabel('x_1'); ylabel('x_2'); grid on; axis tight

% Высокая точность
[t2,x2] = ode45(@(t,x) f(t,x,delta_phase), tspan_long, x0, ...
                odeset('RelTol',1e-15,'AbsTol',1e-15));
figure
plot(x2(:,1),x2(:,2),'r-','LineWidth',1.8)
title('Фазовый портрет с высокой точностью (RelTol=1e-15), δ = 0.12')
xlabel('x_1'); ylabel('x_2'); grid on; axis tight