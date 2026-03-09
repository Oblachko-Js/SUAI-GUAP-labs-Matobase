function [x, y] = get_input_points()
% Ввод значений массива x и y
x_str = strrep(input("Введите значения массива x, разделяя их пробелами: ",'s'), ',', '.');
while true
    x_cell = strsplit(x_str, ' ');
    x = str2double(x_cell);
    if any(isnan(x)) || length(x) < 2 || length(unique(x)) ~= length(x)
        disp("Массив x должен содержать не менее двух уникальных чисел, разделенных пробелами и не буквы.");
        x_str = strrep(input("Введите значения массива x: ", 's'), ',', '.');
        continue
    end
    [~, idx] = sort(x); % сортируем массив x и получаем индексы сортировки
    x = x(idx); % переставляем элементы массива x в соответствии с порядком сортировки
    break
end

y_str = strrep(input("Введите значения массива y, разделяя их пробелами: ",'s'), ',', '.');
while true
    y_cell = strsplit(y_str, ' ');
    y = str2double(y_cell);
    if any(isnan(y)) || length(y) ~= length(x)
        disp("Массив y должен содержать столько же чисел, сколько и массив x, разделенных пробелами и не буквы.");
        y_str = strrep(input("Введите значения массива y: ", 's'), ',', '.');
        continue
    end
    y = y(idx); % переставляем элементы массива y в соответствии с порядком сортировки массива x
    break
end
end