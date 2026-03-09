function [ss_pos] = vstroina(f,A,B)
% Вычисление интеграла встроенной функцией integral для проверки
ss_pos = integral(f,A,B);
end