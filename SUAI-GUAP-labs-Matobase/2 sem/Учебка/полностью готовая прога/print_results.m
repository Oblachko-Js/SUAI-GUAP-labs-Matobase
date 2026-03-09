function print_results(x, y, xx, yy)
clc;
% Вывод результата
% Используем polyfit для вычисления коэффициентов интерполяционного полинома
p = polyfit(x, y, length(x)-1);
% Используем polyval для вычисления значений интерполяционного полинома в точках xx
pp = polyval(p, xx);
fprintf("Таблица значений x и y:\n");
fprintf("  x         y   \n");
for i = 1:length(x)
    fprintf("%.6f   %.6f\n", x(i), y(i));
end
fprintf("\n");
fprintf("Значения полинома в точках:\n");
fprintf("  xx         yy        yy(Matlab)  \n");
for i = 1:length(xx)
    fprintf("%.6f   %.6f   %.6f\n", xx(i), yy(i),pp(i));
end
fprintf("\n");
end