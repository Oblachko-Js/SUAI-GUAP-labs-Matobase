function [e] = e_tochn()
while true
    e_str = input("Введите точность вычисления корня e, используя точку для разделения дробной части: ", 's');
    e_str = strrep(e_str, ',', '.');
    e = str2double(e_str);
    if isnan(e)
        disp("e должно быть числом, в числе должен быть один разделитель.");
        continue
    end
    if e <= 0
        fprintf('Точность должна быть больше нуля, использующая точку в качестве разделителя дробной части\n');
        continue
    end
    break
end
end