function [dfx,x] = nyton(f, x0, e, f_x_vals, f_y_vals)
max_iter = 100;
    for i = 1:max_iter
        fx = f(x0);
        dfx = (f(x0+e) - f(x0-e)) / (2*e); % вычисляем производную через определение
        x = x0 - fx/dfx;
        casatelna(f(x0),x0, f_x_vals, f_y_vals, dfx)
        tochka(x0, f);
        % Проверка критерия окончания итерационного процесса
        if abs(x - x0) < e
            fprintf('Уравнение решено за %d итераций\n', i);
            fprintf('Корень уравнения: %.6f\n', x0);
            % Используем встроенную функцию fzero для получения решения уравнения с точностью e
            x_fzero = fzero(f, x0);
            fprintf('Корень уравнения по встроенной функции fzero: %.6f\n', x_fzero);
            break;
        elseif i == max_iter
            close all
            fprintf('Уравнение не решено за %d итераций\n', max_iter);
            break;
        end
        x0 = x;
    end
end