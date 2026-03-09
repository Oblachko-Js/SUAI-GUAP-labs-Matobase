function vivod(ss_pos, s_new_pos)
fprintf('Интеграл пользовательским методом = %.3f\n', s_new_pos);
fprintf('Интеграл встроенной функцией integral = %.3f\n', ss_pos);
cerror = ss_pos - s_new_pos;
k = -floor(log10(abs(cerror)));
cerror = floor(cerror*(10^k))/10^k;
fprintf('Погрешность интеграла = %.3f\n', cerror);
end