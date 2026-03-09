function F = calculate_divided_differences(x, y)
% Вычисляем разделенные разности
n = length(x);
F = y'; % инициализация матрицы разделенных разностей
for j = 2:n
    for i = 1:n-j+1
        F(i,j) = (F(i+1,j-1) - F(i,j-1))/(x(i+j-1) - x(i));
    end
end
end