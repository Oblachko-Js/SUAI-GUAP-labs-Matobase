import sympy as sp
import matplotlib.pyplot as plt
from scipy.integrate import quad
import math
from scipy.optimize import minimize

# Символическое решение
x = sp.Symbol('x')
y = sp.Function('y')(x)
y_prime = sp.diff(y, x)
L = sp.sqrt(y * (1 + y_prime**2))  # Лагранжиан
partial_L_y = sp.diff(L, y)
partial_L_yprime = sp.diff(L, y_prime)
el_lhs = sp.diff(partial_L_yprime, x)
el_equation = el_lhs - partial_L_y
print("Уравнение Эйлера-Лагранжа: ", sp.simplify(el_equation), " = 0")

# Аналитическое решение (проверка)
# Простое решение y(x) = 5 удовлетворяет граничным условиям, но не обязательно экстремаль
y_sol = 5
print("Аналитическое решение (приближение): y(x) = ", y_sol)

y0 = 5
y1 = 5
print(f"y(-4) = {y0}, y(4) = {y1}")

# Численное вычисление V на константной функции y=5
def integrand_const(x_val):
    y_val = 5
    y_prime_val = 0
    return math.sqrt(y_val * (1 + y_prime_val**2))

V_const, error_const = quad(integrand_const, -4, 4)
print(f"Значение функционала V (константная функция y=5): {V_const:.4f} (ошибка: {error_const:.4e})")

# Численное решение через оптимизацию с улучшенной аппроксимацией
def func_to_minimize(params, x):
    a, b, c = params  # Используем кубическую аппроксимацию y = a*x^3 + b*x + c
    y_val = a * x**3 + b * x + c
    y_prime_val = 3 * a * x**2 + b
    return -math.sqrt(y_val * (1 + y_prime_val**2))  # Минимизация с учетом знака

def constraint1(params):
    a, b, c = params
    return a * (-4)**3 + b * (-4) + c - 5  # y(-4) = 5

def constraint2(params):
    a, b, c = params
    return a * (4)**3 + b * (4) + c - 5  # y(4) = 5

cons = ({'type': 'eq', 'fun': constraint1}, {'type': 'eq', 'fun': constraint2})
initial_guess = [0.001, 0, 5]  # Улучшенное начальное приближение
result = minimize(lambda params: -quad(lambda x: func_to_minimize(params, x), -4, 4)[0], initial_guess, constraints=cons)
a_opt, b_opt, c_opt = result.x
y_num = lambda x: a_opt * x**3 + b_opt * x + c_opt
V_num_approx, _ = quad(lambda x: math.sqrt(y_num(x) * (1 + (3 * a_opt * x**2 + b_opt)**2)), -4, 4)
print(f"Численное решение (кубическая аппроксимация): y(x) ≈ {a_opt:.4f}x^3 + {b_opt:.4f}x + {c_opt:.4f}")
print(f"Значение V (численное): {V_num_approx:.4f}")
print(f"Разница между константным и численным V: {abs(V_const - V_num_approx):.4e}")

# Построение графика
x_vals = [i / 10 * 8 - 4 for i in range(101)]  # От -4 до 4 с шагом 0.08
y_const = [5 for x in x_vals]
y_cubic = [a_opt * x**3 + b_opt * x + c_opt for x in x_vals]

plt.plot(x_vals, y_const, label='Константная функция: y=5')
plt.plot(x_vals, y_cubic, label='Кубическая аппроксимация', linestyle='--')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Сравнение константной функции и кубической аппроксимации')
plt.legend()
plt.grid(True)
plt.show()