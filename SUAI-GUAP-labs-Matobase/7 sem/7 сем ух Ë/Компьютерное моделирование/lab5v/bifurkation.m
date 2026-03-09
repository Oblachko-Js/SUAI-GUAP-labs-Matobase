clear all; close all; clc;

a=1; lambda=1; epsilon=0.01; alpha=0.4;

delta_vec = linspace(0.10, 0.26, 1200);
N_total   = 5000;
N_plot    = 600;

attractor_x1 = zeros(N_plot, length(delta_vec));
attractor_x2 = zeros(N_plot, length(delta_vec));

for k = 1:length(delta_vec)
    delta = delta_vec(k);
    [~,x] = ode45(@(t,x) baz(t,x,a,lambda,epsilon,alpha,delta), ...
                  [0 N_total], [15; 5], odeset('RelTol',1e-10,'AbsTol',1e-12));
    attractor_x1(:,k) = x(end-N_plot+1:end,1);
    attractor_x2(:,k) = x(end-N_plot+1:end,2);
end

figure('Color','w','Position',[100 50 1300 750]);

% —— Верхний график: жертвы ——
subplot(2,1,1);
plot(delta_vec, attractor_x1, '.', 'Color',[0.05 0.45 0.95], 'MarkerSize',2.2);
hold on;
plot(0.2395, 82.5, 'rp', 'MarkerSize',20, 'MarkerFaceColor','red', ...
     'MarkerEdgeColor','k', 'LineWidth',2);
plot([0.2397 0.2397], [0 110], 'r--', 'LineWidth',3);

title('Бифуркационная диаграмма модели Базыкина–Годвинa (вариант 19)', ...
      'FontSize',18,'FontWeight','bold');
ylabel('Численность жертв  x₁(t),  [усл. ед.]', 'FontSize',16,'FontWeight','bold');
text(0.241, 105, '\delta_{кр} \approx 0.2397  (бифуркация Андронова–Хопфа)', ...
     'Color','red','FontSize',15,'FontWeight','bold','BackgroundColor','w');
text(0.15, 35, '\delta = 0.2395 — наиболее чувствительное значение из задания', ...
     'Color','red','FontSize',16,'FontWeight','bold','BackgroundColor','w','EdgeColor','k');

xlim([0.10 0.26]); ylim([0 110]);
grid on; box on;
set(gca,'FontSize',14,'LineWidth',1.2);

% —— Нижний график: хищники ——
subplot(2,1,2);
plot(delta_vec, attractor_x2, '.', 'Color',[0.95 0.35 0.15], 'MarkerSize',2.2);
hold on;
plot(0.2395, 6.1, 'rp', 'MarkerSize',20, 'MarkerFaceColor','red', ...
     'MarkerEdgeColor','k', 'LineWidth',2);
plot([0.2397 0.2397], [0 15], 'r--', 'LineWidth',3);

xlabel('Коэффициент внутривидовой конкуренции хищников  \delta', ...
       'FontSize',16,'FontWeight','bold');
ylabel('Численность хищников  x₂(t),  [усл. ед.]', ...
       'FontSize',16,'FontWeight','bold');

xlim([0.10 0.26]); ylim([0 15]);
grid on; box on;
set(gca,'FontSize',14,'LineWidth',1.2);

%% Функция модели
function dx = baz(~,x,a,lambda,epsilon,alpha,delta)
    dx = [a*x(1) - x(1)*x(2)/(1+alpha*x(1)) - epsilon*x(1)^2;
          -lambda*x(2) + x(1)*x(2)/(1+alpha*x(1)) - delta*x(2)^2];
end