function [x,y,xx] = vvvvooooodddd()
% Ввод значений массива x
x_str = strrep(input("Введите значения массива x, разделяя их пробелами: ",'s'), ',', '.');
while true
x_cell = strsplit(x_str, ' ');
x = str2double(x_cell);
if any(isnan(x)) || length(x) < 2 || length(unique(x)) ~= length(x)
disp("Массив x должен содержать не менее двух уникальных чисел, разделенных пробелами.");
x_str = strrep(input("Введите значения массива x: ", 's'), ',', '.');
continue
end
break
end
% Ввод значений массива y
y_str = strrep(input("Введите значения массива y, разделяя их пробелами: ",'s'), ',', '.');
while true
y_cell = strsplit(y_str, ' ');
y = str2double(y_cell);
if any(isnan(y)) || length(y) ~= length(x)
disp("Массив y должен содержать столько же чисел, сколько и массив x, разделенных пробелами.");
y_str = strrep(input("Введите значения массива y: ", 's'), ',', '.');
continue
end
break
end
% Ввод значения xx
xx_str = strrep(input("Введите значение xx, используя точку для разделения дробной части: ", 's'), ',', '.');
while true
xx = str2double(xx_str);
if isnan(xx)
disp("xx должно быть числом, в числе должен быть один разделитель.");
xx_str = strrep(input("Введите значение xx: ", 's'), ',', '.');
continue
end
break
end
end