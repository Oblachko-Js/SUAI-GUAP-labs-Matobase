function [x0] = x0_nach()
x0_str = input("Введите начальное приближенное значение x0, используя точку для разделения дробной части: ", 's');
while true
    x0_str = strrep(x0_str, ',', '.');
    x0 = str2double(x0_str);
    if isnan(x0)
        disp("x0 должно быть числом, в числе должен быть один разделитель.");
        x0_str = input("Введите значение x0: ", 's');
        continue
    end
    
    break
end
end