import time

# Итеративная функция для вычисления f(x, y) = 3x - y
def iterative_f(x, y):
    result = 0
    for _ in range(x):
        result += 3
    return result - y

# Вспомогательная рекурсивная функция для вычисления 3x
def mul3(x):
    if x == 0:
        return 0
    return mul3(x - 1) + 3

# Рекурсивная функция для вычисления f(x, y) = 3x - y
def recursive_f(x, y):
    return mul3(x) - y

# Основная программа
def main():
    try:
        # Ввод аргументов пользователем
        x = int(input("Введите x: "))
        y = int(input("Введите y: "))
        
        # Проверка на неотрицательное x для рекурсии
        if x < 0:
            print("Ошибка: x должен быть неотрицательным для вычислений.")
            return
        
        # Измерение времени для итеративного метода
        start_time = time.time()
        iter_result = iterative_f(x, y)
        iter_time = time.time() - start_time
        
        # Измерение времени для рекурсивного метода
        start_time = time.time()
        rec_result = recursive_f(x, y)
        rec_time = time.time() - start_time
        
        # Вывод результатов
        print(f"Итеративный результат: f({x}, {y}) = {iter_result}")
        print(f"Время итеративного метода: {iter_time:.6f} секунд")
        print(f"Рекурсивный результат: f({x}, {y}) = {rec_result}")
        print(f"Время рекурсивного метода: {rec_time:.6f} секунд")
        
    except ValueError:
        print("Ошибка: Введите целые числа для x и y.")

# Запуск программы
if __name__ == "__main__":
    main()