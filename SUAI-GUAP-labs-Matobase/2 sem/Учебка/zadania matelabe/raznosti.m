function [i,y,x] = raznosti(x,y)
n = length(x); % определение переменной n
% Вычисление разделенных разностей
for i = 2:n
    for j = n:-1:i
        kaka = x(j) - x(j-i+1);
        if kaka == 0
            disp('Нельзя делить на ноль');
            return
        end
        y(j) = (y(j) - y(j-1))/kaka;
    end
end
end