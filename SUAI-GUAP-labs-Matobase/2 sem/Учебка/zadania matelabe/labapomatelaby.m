clc;
clear;
fprintf ("Автор Панченко Андрей\n");
while true
    x_str = input("Введите номер лабораторной работы: ", 's');
    x_str = str2double(x_str);
    if isnan(x_str)
        disp("Номер должен быть числом, вы чё?");
        continue
    end
    if x_str <= 0 || x_str > 3
        fprintf('Номеров 3 ну чё вы делаете.\n');
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
end