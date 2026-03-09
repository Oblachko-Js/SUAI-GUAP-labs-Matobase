function [x_vals, y_vals] = graf(f)
while true
    x_min_str = input('Введите левое значение оси x: ', 's');
    x_min_str = strrep(x_min_str, ',', '.');
    x_min_str = str2double(x_min_str);
    if isnan(x_min_str)
        disp("Левая граница должна быть числом, в числе должен быть один разделитель.");
        continue
    end
    x_max_str = input('Введите правое значение оси x: ','s');
    x_max_str = strrep(x_max_str, ',', '.');
    x_max_str = str2double(x_max_str);
    if isnan(x_max_str)
        disp("Правая граница должна быть числом, в числе должен быть один разделитель.");
        continue
    end
    if (x_min_str > x_max_str || x_max_str < x_min_str || x_min_str == x_max_str)
        fprintf("Левая граница не может быть больше правого и наоборот, а также не должны быть равны.\n");
        continue
    end
    break
end
x_vals = x_min_str : 0.1 : x_max_str;
y_vals = f(x_vals);
plot(x_vals, y_vals, 'b', 'LineWidth', 2);
hold on;
line([x_min_str, x_max_str], [0, 0], 'Color', 'k', 'LineWidth', 1); % ось x
line([0, 0], [min(y_vals), max(y_vals)], 'Color', 'k', 'LineWidth', 1); % ось y
xlim([x_min_str, x_max_str]);
ylim([min(y_vals), max(y_vals)]);
axis('tight');
xlabel('Ось X');
ylabel('Ось Y');
grid on;
drawnow;
output_args = {x_vals, y_vals};
end