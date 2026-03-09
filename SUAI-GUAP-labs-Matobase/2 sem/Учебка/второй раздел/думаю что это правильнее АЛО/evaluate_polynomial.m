function yy = evaluate_polynomial(x,y, xx)
% Вычисление значения полинома для всех заданных точек

% Вычисляем разделенные разности
F = calculate_divided_differences(x, y);

yy = zeros(size(xx));
n = length(x);
for k = 1:length(xx)
    xk = xx(k);
    Pk = F(1,1);
    for j=2:n
        prod = 1;
        for i=1:j-1
            prod = prod * (xk - x(i));
        end
        Pk = Pk + F(1,j)*prod;
    end
    yy(k) = Pk;
end
end