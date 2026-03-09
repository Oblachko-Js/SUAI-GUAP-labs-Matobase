import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import linprog

# Определение функции целей и ограничений
c = [-2, -5]  # Минимизируем -z, так как linprog минимизирует

# Ограничения в виде Ax <= b
A = [[-5, -1],  # 5x1 + x2 >= 5
     [-3, -1],  # 3x1 + x2 >= 6
     [-4, -3]]  # 4x1 + 3x2 >= 4

b = [-5, -6, -4]

# Ограничение на неотрицательность переменных x1 и x2
x1_bounds = (0, None)
x2_bounds = (0, None)

# Решение задачи
res = linprog(c, A_ub=A, b_ub=b, bounds=[x1_bounds, x2_bounds], method='highs')

# Проверка статуса решения
if res.success:
    print("Оптимальное значение переменных x1 и x2:", res.x)
    print("Максимальное значение целевой функции:", -res.fun)
else:
    # Проверяем причину неудачи
    if res.status == 3:
        print("Функция не ограничена. Оптимальное решение отсутствует.")
    else:
        print("Решение не найдено. Статус:", res.message)

# Графическая визуализация
x = np.linspace(0, 10, 500)

# Построение линий ограничений
y1 = 5 - 5*x    # 5x1 + x2 >= 5
y2 = 6 - 3*x    # 3x1 + x2 >= 6
y3 = (4 - 4*x) / 3  # 4x1 + 3x2 >= 4

plt.plot(x, y1, label=r'$5x_1 + x_2 \geq 5$')
plt.plot(x, y2, label=r'$3x_1 + x_2 \geq 6$')
plt.plot(x, y3, label=r'$4x_1 + 3x_2 \geq 4$')

# Найдем области пересечения
y1_fill = np.maximum(y1, 0)
y2_fill = np.maximum(y2, 0)
y3_fill = np.maximum(y3, 0)

plt.fill_between(x, np.minimum(y1_fill, y2_fill), np.minimum(y1_fill, y3_fill), where=(y1_fill >= 0) & (y2_fill >= 0) & (y3_fill >= 0), color='gray', alpha=0.3)

# Оформление графика
plt.xlim(0, 10)
plt.ylim(0, 10)
plt.xlabel(r'$x_1$')
plt.ylabel(r'$x_2$')
plt.legend()
plt.grid(True)
plt.title('Графическое решение задачи линейного программирования')

# Показать график
plt.show()
