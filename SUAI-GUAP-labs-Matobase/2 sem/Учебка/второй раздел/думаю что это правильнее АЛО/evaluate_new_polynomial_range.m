function [x_range_new, y_range_new] = evaluate_new_polynomial_range(F_new, x_new)
% Интерполируем полином на интервале от минимального значения x до максимального значения xx
x_range_new = linspace(min(x_new), max(x_new), 100);
y_range_new = zeros(size(x_range_new));
n_new = length(x_new);
for i=1:length(x_range_new)
    P = F_new(1,1);
    for j=2:n_new
        prod = 1;
        for k=1:j-1
            prod = prod * (x_range_new(i) - x_new(k));
        end
        P = P + F_new(1,j)*prod;
    end
    y_range_new(i) = P;
end
end