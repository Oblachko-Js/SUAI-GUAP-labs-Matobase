import sympy as sp
import matplotlib.pyplot as plt
from scipy.integrate import quad
import math
from scipy.optimize import minimize

# Символическое решение
x = sp.Symbol('x')
y = sp.Function('y')(x)
y_prime = sp.diff(y, x)
F = x * y * y_prime - 2 * y_prime**2
partial_F_y = sp.diff(F, y)
partial_F_yprime = sp.diff(F, y_prime)
el_lhs = sp.diff(partial_F_yprime, x)
el_equation = el_lhs - partial_F_y
print("Уравнение Эйлера-Лагранжа: ", sp.simplify(el_equation), " = 0")

y_sol = 0.5 * sp.cosh(x / 2)
print("Аналитическое решение: y(x) = ", y_sol)

y0 = 1
y1 = math.cosh(0.5)
print(f"y(0) = {y0}, y(1) = {y1:.4f}")

# Численное вычисление V на экстремали
def integrand(x_val):
    y_val = 0.5 * math.cosh(x_val / 2)
    y_prime_val = 0.25 * math.sinh(x_val / 2)
    return x_val * y_val * y_prime_val - 2 * (y_prime_val)**2

V_num, error = quad(integrand, 0, 1)
print(f"Значение функционала V (аналитическая экстремаль): {V_num:.4f} (ошибка: {error:.4e})")

# Численное решение через оптимизацию
def func_to_minimize(params, x):
    a, b = params
    y_val = a * x + b
    y_prime_val = a
    return x * y_val * y_prime_val - 2 * y_prime_val**2

def constraint1(params):
    return params[1] - 1

def constraint2(params):
    a, b = params
    return a + b - math.cosh(0.5)

cons = ({'type': 'eq', 'fun': constraint1}, {'type': 'eq', 'fun': constraint2})
initial_guess = [0.1, 0.9]
result = minimize(lambda params: -quad(lambda x: func_to_minimize(params, x), 0, 1)[0], initial_guess, constraints=cons)
a_opt, b_opt = result.x
y_num = lambda x: a_opt * x + b_opt
V_num_approx, _ = quad(lambda x: func_to_minimize([a_opt, b_opt], x), 0, 1)
print(f"Численное решение (линейная аппроксимация): y(x) ≈ {a_opt:.4f}x + {b_opt:.4f}")
print(f"Значение V (численное): {V_num_approx:.4f}")
print(f"Разница между аналитическим и численным V: {abs(V_num - V_num_approx):.4e}")

# Построение графика
x_vals = [i / 100 for i in range(101)]  # От 0 до 1 с шагом 0.01
y_analyt = [0.5 * math.cosh(x / 2) for x in x_vals]
y_linear = [a_opt * x + b_opt for x in x_vals]

plt.plot(x_vals, y_analyt, label='Аналитическая экстремаль: 0.5 cosh(x/2)')
plt.plot(x_vals, y_linear, label='Линейная аппроксимация', linestyle='--')
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Сравнение экстремали и линейной аппроксимации')
plt.legend()
plt.grid(True)
plt.show()