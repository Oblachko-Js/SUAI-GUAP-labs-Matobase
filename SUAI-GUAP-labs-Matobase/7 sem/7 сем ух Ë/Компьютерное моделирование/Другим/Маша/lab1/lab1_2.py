import sympy as sp
import matplotlib.pyplot as plt
from scipy.integrate import quad
import math
from scipy.optimize import minimize

# Символическое решение
x = sp.Symbol('x')
y = sp.Function('y')(x)
y_prime = sp.diff(y, x)
L = y_prime / sp.sqrt(1 + y_prime**2)  # Лагранжиан
partial_L_y = sp.diff(L, y)
partial_L_yprime = sp.diff(L, y_prime)
el_lhs = sp.diff(partial_L_yprime, x)
el_equation = el_lhs - partial_L_y
print("Уравнение Эйлера-Лагранжа: ", sp.simplify(el_equation), " = 0")

# Аналитическое решение
y_sol = x + 1
print("Аналитическое решение (приближение): y(x) = ", y_sol)

y0 = 1
y1 = 4
print(f"y(0) = {y0}, y(3) = {y1}")

# Численное вычисление V на линейной функции y = x + 1
def integrand_linear(x_val):
    y_val = x_val + 1
    y_prime_val = 1
    return y_prime_val / math.sqrt(1 + y_prime_val**2)

V_linear, error_linear = quad(integrand_linear, 0, 3)
print(f"Значение функционала V (линейная функция y=x+1): {V_linear:.4f} (ошибка: {error_linear:.4e})")

# Численное решение через оптимизацию
def func_to_minimize(params, x):
    a, b, c = params  # y = a*x^3 + b*x + c
    y_val = a * x**3 + b * x + c
    y_prime_val = 3 * a * x**2 + b
    return y_prime_val / math.sqrt(1 + y_prime_val**2)  # Минимизация V

def constraint1(params):
    a, b, c = params
    return a * (0)**3 + b * (0) + c - 1  # y(0) = 1

def constraint2(params):
    a, b, c = params
    return a * (3)**3 + b * (3) + c - 4  # y(3) = 4

cons = ({'type': 'eq', 'fun': constraint1}, {'type': 'eq', 'fun': constraint2})
initial_guess = [0.001, 1.0, 1.0]  # Начальное приближение с малым a
bounds = [(-0.05, 0.05), (0.8, 1.2), (0.8, 1.2)]  # Расширенные границы для a
result = minimize(lambda params: quad(lambda x: func_to_minimize(params, x), 0, 3)[0], initial_guess, bounds=bounds, constraints=cons, method='SLSQP')
a_opt, b_opt, c_opt = result.x
y_num = lambda x: a_opt * x**3 + b_opt * x + c_opt
V_num_approx, _ = quad(lambda x: (3 * a_opt * x**2 + b_opt) / math.sqrt(1 + (3 * a_opt * x**2 + b_opt)**2), 0, 3)
print(f"Численное решение (кубическая аппроксимация): y(x) ≈ {a_opt:.6f}x^3 + {b_opt:.6f}x + {c_opt:.6f}")
print(f"Значение V (численное): {V_num_approx:.6f}")
print(f"Разница между линейным и численным V: {abs(V_linear - V_num_approx):.6e}")

# Проверка значений
print(f"Проверка y(0): {y_num(0):.6f} (должно быть 1)")
print(f"Проверка y(3): {y_num(3):.6f} (должно быть 4)")

# Построение графика
x_vals = [i / 10 * 3 for i in range(31)]  # От 0 до 3
y_linear = [x + 1 for x in x_vals]
y_cubic = [y_num(x) for x in x_vals]

plt.plot(x_vals, y_linear, label='Линейная функция: y=x+1')
plt.plot(x_vals, y_cubic, label='Кубическая аппроксимация', linestyle='--')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Сравнение линейной функции и кубической аппроксимации')
plt.legend()
plt.grid(True)
plt.xlim(0, 3)  # Ограничение оси x до [0, 3]
plt.ylim(0, 5)  # Ограничение оси y
plt.show()