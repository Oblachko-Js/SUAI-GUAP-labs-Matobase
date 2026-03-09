function [f] = Test_cur()
clear;
clc;
while true
    f_str = input('Введите функцию: ','s');
    f_str = strcat('@(x)', f_str);
    if isempty(f_str)
        disp("Функция не может быть пустой.");
        continue
    end
    % Проверка введенной функции на корректность
    if contains(f_str, ';') || contains(f_str, 'eval') || contains(f_str, 'feval') || contains(f_str, 'for') || contains(f_str, 'while')
        disp("Запрещенные символы или функции в строке функции.");
        continue
    end
    if contains(f_str, '^') && ~contains(f_str, '.^')
        disp("Используйте оператор '.^' для возведения в степень с плавающей точкой.");
        continue
    end
    if contains(f_str, '*') && ~contains(f_str, '.*')
        disp("Используйте оператор '.*' для умножения.");
        continue
    end
    if contains(f_str, '/') && ~contains(f_str, './')
        disp("Используйте оператор './' для деления.");
        continue
    end
    try
        % Проверка, что функция начинается с '@(x)'
        if ~startsWith(f_str, '@(x)')
            error('Функция должна начинаться с "@(x)".');
        end
        % Выполнение функции для проверки, что она корректно определена
        f = str2func(f_str);
        x_test = f(0);
        break % прерываем цикл, если функция корректно определена
    catch ME
        disp(ME.message);
        continue % повторяем цикл, если функция некорректно определена
    end
end
end