clear all; close all; clc;

a = 1;
lambda = 1;
epsilon = 0.01;
alpha = 0.4;
delta = 0.12;

x1_star = 80;
x2_star = 6;

k1 = 1.0;
k2 = 1.5;
t_switch = 80;

x0 = [15; 8];
tspan = [0 200];

[t,x] = ode45(@(t,x) controlled_model(t,x,a,lambda,epsilon,alpha,delta,...
                                      x1_star,x2_star,k1,k2,t_switch), tspan, x0);

figure(1);
plot(t,x(:,1),'b','LineWidth',1.8); hold on;
plot(t,x(:,2),'r--','LineWidth',1.8);
plot([t_switch t_switch],[0 max(x(:,1))],'k:','LineWidth',1.5);
xlabel('Время t'); ylabel('Популяции');
title('x_1(t) и x_2(t) (синий — жертвы, красный — хищники)');
legend('x_1','x_2','включение управления');
grid on;

figure(2);
plot(x(t<=t_switch,1),x(t<=t_switch,2),'b','LineWidth',2); hold on;
plot(x(t>t_switch,1),x(t>t_switch,2),'r','LineWidth',2.5);
plot(x1_star,x2_star,'kp','MarkerSize',14,'MarkerFaceColor','k');
xlabel('x_1 (жертвы)'); ylabel('x_2 (хищники)');
title('Фазовый портрет: синий — без управления, красный — с управлением');
legend('неуправляемая','управляемая','целевая точка');
grid on;

u1 = -k1*(x(:,1)-x1_star).*(t>=t_switch);
u2 = -k2*(x(:,2)-x2_star).*(t>=t_switch);
figure(3);
plot(t,u1,'b','LineWidth',1.8); hold on;
plot(t,u2,'r--','LineWidth',1.8);
xlabel('Время t'); ylabel('Управление');
title('Сигналы управления u_1 и u_2');
legend('u_1','u_2');
grid on;

function dxdt = controlled_model(t,x,a,lambda,epsilon,alpha,delta,...
                                 x1_star,x2_star,k1,k2,t_switch)
    x1 = x(1); x2 = x(2);
    
    dx1 = a*x1 - (x1*x2)/(1+alpha*x1) - epsilon*x1^2;
    dx2 = -lambda*x2 + (x1*x2)/(1+alpha*x1) - delta*x2^2;
    
    if t >= t_switch
        u1 = -k1*(x1 - x1_star);
        u2 = -k2*(x2 - x2_star);
    else
        u1 = 0; u2 = 0;
    end
    
    dxdt = [dx1 + u1; dx2 + u2];
end