clear;
clc;
%Вводим данные
[f] = Test_cur();
%График
[f_x_vals, f_y_vals] = graf(f);
[x0] = x0_nach;
[e] = e_tochn;
% Итерационный процесс метода Ньютона
nyton(f, x0, e, f_x_vals, f_y_vals);