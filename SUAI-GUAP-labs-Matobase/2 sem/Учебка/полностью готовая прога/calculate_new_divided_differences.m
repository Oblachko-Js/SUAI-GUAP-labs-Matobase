function F_new = calculate_new_divided_differences(x_new, y_new)
% Вычисляем новые разделенные разности
n_new = length(x_new);
F_new = zeros(n_new);
F_new(:,1) = y_new'; % инициализация матрицы разделенных разностей
for j = 2:n_new
    for i = 1:n_new-j+1
        F_new(i,j) = (F_new(i+1,j-1) - F_new(i,j-1))/(x_new(i+j-1) - x_new(i));
    end
end
end