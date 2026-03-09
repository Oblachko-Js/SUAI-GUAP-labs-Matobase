% Пункт 3 — Вариант 25 
clear all; close all; clc;

%% Параметры модели 
a       = 1;
lambda  = 1;
epsilon = 0.01;
alpha   = 0.4;
k       = 40;                       % коэффициент усиления управления

%% Сетка параметров
delta_vec = linspace(0.10, 0.26, 100);     % 100 точек от 0.10 до 0.26
x20_vec   = 2:0.5:14;                      % желаемые значения хищников

% Принудительно добавляем наши четыре значения δ, чтобы они точно были
delta_vec = sort(unique([delta_vec, 0.12, 0.215, 0.221, 0.2395]));

%% Матрица результатов
X2_steady = zeros(length(x20_vec), length(delta_vec));

x0    = [20; 8];
tspan = [0 120];

%% Основной цикл расчёта установившихся режимов
for i = 1:length(delta_vec)
    delta = delta_vec(i);
    for j = 1:length(x20_vec)
        x20 = x20_vec(j);
        
        [~,sol] = ode45(@(t,x) model_control(t,x,a,lambda,epsilon,alpha,delta,x20,k), ...
                        tspan, x0, odeset('RelTol',1e-9));
                    
        X2_steady(j,i) = mean(sol(end-20:end,2));   % установившееся значение x₂
    end
end

%% Находим точные индексы наших четырёх δ
[~,i1] = min(abs(delta_vec-0.215));
[~,i2] = min(abs(delta_vec-0.221));
[~,i3] = min(abs(delta_vec-0.2395));
[~,i4] = min(abs(delta_vec-0.12));

%% Рисуем красивую картинку
figure('Position',[100 100 1200 750],'Color','w');

subplot(2,2,1)
imagesc(delta_vec, x20_vec, X2_steady); axis xy; colorbar;
hold on;
plot([0.215 0.215],ylim,'w--','LineWidth',2.5);
plot([0.221 0.221],ylim,'w--','LineWidth',2.5);
plot([0.2395 0.2395],ylim,'w--','LineWidth',2.5);
plot([0.12 0.12],ylim,'w--','LineWidth',2.5);
xlabel('\delta'); ylabel('Заданное x_{20}');
title('Достигнутое значение x_2');
caxis([2 14]); colormap parula;

subplot(2,2,2)
plot(delta_vec, X2_steady', 'LineWidth',1.3); hold on;
for xx = x20_vec(1:4:end)
    plot(delta_vec, xx*ones(size(delta_vec)), 'k:', 'LineWidth',1);
end
xlabel('\delta'); ylabel('x_2^{уст}');
title('Сечения по x_{20}'); grid on;

subplot(2,2,3)
plot(x20_vec, X2_steady(:,i1), 'o-', 'LineWidth',2.2); hold on;
plot(x20_vec, X2_steady(:,i2), 's-', 'LineWidth',2.2);
plot(x20_vec, X2_steady(:,i3), '^-', 'LineWidth',2.2);
plot(x20_vec, X2_steady(:,i4), 'd-', 'LineWidth',2.2);
plot(x20_vec, x20_vec, 'k--', 'LineWidth',2);
xlabel('Заданное x_{20}'); ylabel('Достигнутое x_2');
title('Точность отработки при δ из задания');
legend('δ = 0.215','δ = 0.221','δ = 0.2395','δ = 0.12','идеальная линия', ...
       'Location','southeast');
grid on;

subplot(2,2,4)
err = abs(X2_steady - x20_vec');
plot(delta_vec, mean(err,1), '-o','Color',[0.2 0.2 0.2],'LineWidth',2.5);
xlabel('\delta'); ylabel('Средняя ошибка |x_2 - x_{20}|');
title('Качество управления'); grid on;
ylim([0 0.4]);

sgtitle('Пункт 3. Сценарий управления ψ = x_2 – x_{20} → 0 (вариант 25)', ...
        'FontSize',16,'FontWeight','bold');

%% Функция модели с управлением 
function dxdt = model_control(~,x,a,lambda,epsilon,alpha,delta,x20,k)
    x1 = x(1);
    x2 = x(2);
    u  = -k * (x2 - x20);                     % наш закон управления
    dxdt = [ a*x1 - x1*x2/(1+alpha*x1) - epsilon*x1^2 ;
            -lambda*x2 + x1*x2/(1+alpha*x1) - delta*x2^2 + u ];
end