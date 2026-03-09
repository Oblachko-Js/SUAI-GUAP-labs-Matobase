clc;
clear;
    disp('Главное меню');
    disp('Выберите пункт меню');
    disp('1. Демонстрационный пример');
    disp('2. Работа с данными пользователя');
    disp('3. Информация об авторе и программе');
    disp('4. Выход');
while true
    x_str = input('Выберите номер пункта программы ','s');
    x_str = str2double(x_str);
    if isnan(x_str)
        disp("Номер должен быть числом, вы чё?");
        continue
    end
    if x_str < 1 || x_str > 4
        fprintf('Номеров 4 ну чё вы делаете.\n');
        continue
    end
    break
end
if x_str == 1
    run ('interpolacya.m');
    return;
end
if x_str == 2
    run ('testaaaaaaaa.m');
    return;
end
if x_str == 3
    run ('infa_2_razdel.m')
    return;
end
if x_str == 4
clc; clear; close;
disp('Работа программы завершена');
end