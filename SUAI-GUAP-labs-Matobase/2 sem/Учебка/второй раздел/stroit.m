function stroit(x,y,xx,yy)
clc;
% Вывод результата
ylim([0, inf]);
plot(x,y,'o',xx,yy);
hold on;
plot(x,y,'k');
fprintf ("Ответ: %.6f\n", yy);
end