function xx = get_xx_input(x)
% Ввод значения xx
xx_str = strrep(input("Введите значения xx, разделяя их пробелами или запятыми и используя точку для разделения дробной части: ", 's'), ',', '.');
while true
    xx_cell = strsplit(xx_str, {' ', ','});
    xx = str2double(xx_cell);
    if any(isnan(xx))
        disp("xx должно быть числом, в числе должен быть один разделитель.");
        xx_str = strrep(input("Введите значения xx: ", 's'), ',', '.');
        continue
    end
    if any(ismember(xx, x))
        disp("Введите значения xx, которые не совпадают с значениями в массиве x.");
        xx_str = strrep(input("Введите значения xx: ", 's'), ',', '.');
        continue
    end
    break
end
end