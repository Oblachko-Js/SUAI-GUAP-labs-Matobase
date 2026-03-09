% Вариант 25: f(u) = (5u² + 4)/(2u² + 3u + 4)
clear; clc;

% Задаём значения входа u
u = [-3, -2, -1, -0.5, 0, 0.5, 1, 1.5, 2, 3, 4, 5]';  

% Считаем f(u)
fu = (5*u.^2 + 4) ./ (2*u.^2 + 3*u + 4);

% Выводим красивую таблицу в командное окно
disp('    u         f(u)    ')
disp('------------------------')
for i = 1:length(u)
    fprintf('%6.2f     %8.4f\n', u(i), fu(i))
end

% Строим график статической характеристики
figure('Position',[100 100 800 600],'Color','w');
plot(u, fu, 'bo-','LineWidth',2,'MarkerFaceColor','b');
hold on;
plot(u, fu, 'b.','MarkerSize',20);
grid on; box on;

% Делаем красиво
xlabel('Входное воздействие u','FontSize',14);
ylabel('Выход нелинейности f(u)','FontSize',14);
title('Статическая характеристика нелинейного элемента (вариант 25)','FontSize',16,'FontWeight','bold');
set(gca,'FontSize',12,'LineWidth',1.2);

% Добавляем сетку значений из таблицы на график
text(u+0.1, fu+0.05, cellstr(num2str(fu,'%.3f')), 'FontSize',10,'Color','red');