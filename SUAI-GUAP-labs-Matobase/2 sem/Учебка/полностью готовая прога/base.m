clc;
clear;
% Ввод значений массива x и y
[x, y] = get_input_points();
% Ввод значения xx
xx = get_xx_input(x);
% Вычисление значения полинома для всех заданных точек
yy = evaluate_polynomial(x,y, xx);
print_results(x, y, xx, yy);
% Построение графика
plot_polynomial(x, y, xx, yy);