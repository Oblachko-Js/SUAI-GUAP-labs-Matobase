function [x_range, y_range] = evaluate_polynomial_range(F, x, xx)
% Строим график полинома, проходящего через заданные точки и точки, добавленные пользователем
x_range = linspace(min([x xx]), max([x xx]), 10000);
y_range = zeros(size(x_range));
n = length(x);
for i=1:length(x_range)
    P = F(1,1);
    for j=2:n
        prod = 1;
        for k=1:j-1
            prod = prod * (x_range(i) - x(k));
        end
        P = P + F(1,j)*prod;
    end
    y_range(i) = P;
end
end