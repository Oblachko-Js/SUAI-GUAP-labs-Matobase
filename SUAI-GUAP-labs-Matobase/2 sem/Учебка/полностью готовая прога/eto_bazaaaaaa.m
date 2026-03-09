clc;
clear;
% Ввод значений
[f,A,B,tol] = vvod();
% Вычисление интеграла методом Симпсона с заданной точностью
[s_new_pos] = sympson_kavo(f,A,B,tol);
% Вычисление с помощью встроенных функции matlab
[ss_pos] = vstroina(f,A,B);
% Вывод результатов
vivod(ss_pos, s_new_pos);
grafik_hi(A, B, f);