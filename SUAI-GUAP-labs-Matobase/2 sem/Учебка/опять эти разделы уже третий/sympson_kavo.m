function [s_new_pos] = sympson_kavo(f,A,B,tol)
% Вычисление интеграла методом Симпсона с заданной точностью
n = 2;
s_old = 0;
s_new_pos = (B-A)*(f(A) + 4*f((A+B)/2) + f(B))/6;
while abs((s_new_pos - s_old)/s_new_pos) > tol && n <= 100
    s_old = s_new_pos;
    n = n * 2;
    dx = (B-A)/n;
    s_new_pos = 0;
    for i = 0:2:n-2
        x1 = A + dx*i;
        x2 = A + dx*(i+2);
        s_new_pos = s_new_pos + (dx/3)*(f(x1)+4*f(x1+dx)+f(x2));
    end
end
end