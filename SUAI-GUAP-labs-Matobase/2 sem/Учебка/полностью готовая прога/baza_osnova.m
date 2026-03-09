clear;
clc;
    disp('Главное меню');
    disp('Эта программа разработана для решения трёх численных методов');
    disp('Выберите пункт меню');
    disp('1. Решение нелинейного уравнения методом Ньютона(касательные)');
    disp('2. Интерполирование функции по формулам Ньютона');
    disp('3. Численное интегрирование методом Симпсона');
    disp('4. Информация об авторе');
    disp('5. Выход');
while true
    x_str = input('Выберите номер пункта программы ','s');
    x_str = str2double(x_str);
    if isnan(x_str)
        disp("Некоректно введен пункт");
        continue
    end
    if x_str < 1 || x_str > 5
        fprintf('Некоректно введен пункт.\n');
        continue
    end
    break
end
if x_str == 1
    run ('eto_1_razdel.m');
    return;
end
if x_str == 2
    run ('eto_2_razdel.m');
    return;
end
if x_str == 3
    run ('eto_3_razdel.m');
    return;
end
if x_str == 4
    run ('infa_obo_mne.m');
    return;
end
if x_str == 5
clc; clear; close;
disp('Работа программы завершена');
end