import sympy as sp
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Определение переменных
x = sp.symbols('x')
y = sp.Function('y')(x)

# Уравнение 1
equation1 = sp.Eq(sp.Derivative(y, x), (3*x - 1)**(1/4) / (y**3 * sp.sin(y**4)))
solution1 = sp.dsolve(equation1, y)
print("Solution to Equation 1:")
if isinstance(solution1, list):
    for sol in solution1:
        print(sp.simplify(sol))
else:
    print(sp.simplify(solution1))

# Уравнение 2
equation2 = sp.Eq(sp.Derivative(y, x), (x**2 + x*y + 4*y**2) / x**2)
solution2 = sp.dsolve(equation2, y)
print("\nSolution to Equation 2:")
if isinstance(solution2, list):
    for sol in solution2:
        print(sp.simplify(sol))
else:
    print(sp.simplify(solution2))

# Уравнение 3
equation3 = sp.Eq(sp.Derivative(y, x), x*y + sp.exp(x**2 / 2))
solution3 = sp.dsolve(equation3, y)
print("\nSolution to Equation 3:")
if isinstance(solution3, list):
    for sol in solution3:
        print(sp.simplify(sol))
else:
    print(sp.simplify(solution3))

# Уравнение 4
equation4 = sp.Eq(sp.Derivative(y, x) - y / x, x**2 / y)
solution4 = sp.dsolve(equation4, y)
print("\nSolution to Equation 4:")
if isinstance(solution4, list):
    for sol in solution4:
        print(sp.simplify(sol))
else:
    print(sp.simplify(solution4))

# Уравнение 7: Система уравнений второго порядка
y1 = sp.Function('y1')(x)
y2 = sp.Function('y2')(x)
ode7 = [sp.Derivative(y1, x) - y2,
         sp.Derivative(y2, x) - x * sp.exp(-x)]

solution7_y1 = sp.dsolve(ode7[0], y1)  
solution7_y2 = sp.dsolve(ode7[1].subs(y1, solution7_y1.rhs), y2)  
print("\nSolution to Equation 7:")
print("y(x):", sp.simplify(solution7_y1))
print("y'(x):", sp.simplify(solution7_y2))

# Уравнение 8: Второй порядок
y8 = sp.Function('y8')(x)
equation8 = sp.Eq(sp.Derivative(y8, x, 2) + 4*sp.Derivative(y8, x) + 3*y8, x * sp.exp(-x))
solution8 = sp.dsolve(equation8, y8)
print("\nSolution to Equation 8:")
print(sp.simplify(solution8))

# Функция для построения графиков численных решений
def plot_numerical_solution(ode_func, title, y0, x_range):
    # Численное решение
    sol = solve_ivp(ode_func, x_range, y0, t_eval=np.linspace(x_range[0], x_range[1], 100))
    
    # Построение графика
    plt.plot(sol.t, sol.y[0], label='y(x)')
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title(title)
    plt.legend()
    plt.grid()
    plt.show()

# Определение функций для численных решений
def ode1(x, y):
    return (3*x - 1)**(1/4) / (y**3 * np.sin(y**4))

def ode2(x, y):
    return (x**2 + x*y + 4*y**2) / x**2

def ode3(x, y):
    return x*y + np.exp(x**2 / 2)

def ode4(x, y):
    return y/x + x**2 / y

def ode7(t, y):
    return [y[1], t * np.exp(-t)]

def ode8(t, y):
    return [y[1], t * np.exp(-t) - 4*y[1] - 3*y[0]]

# Начальные условия и диапазоны для графиков
y0_1 = [1]  # Начальное значение для уравнения 1
y0_2 = [1]  # Начальное значение для уравнения 2
y0_3 = [1]  # Начальное значение для уравнения 3
y0_4 = [1]  # Начальное значение для уравнения 4
y0_7 = [1, 0]  # Начальные условия для системы уравнений 7
y0_8 = [0, 0]   # Начальные условия для уравнения 8

# Диапазоны значений x
x_range_1 = [0.5, 2]
x_range_2 = [0.5, 2]
x_range_3 = [0.5, 2]
x_range_4 = [0.5, 2]
x_range_7 = [0, 5]
x_range_8 = [0, 5]

# Построение графиков для каждого уравнения
plot_numerical_solution(ode1, "Numerical Solution to Equation 1", y0_1, x_range_1)
plot_numerical_solution(ode2, "Numerical Solution to Equation 2", y0_2, x_range_2)
plot_numerical_solution(ode3, "Numerical Solution to Equation 3", y0_3, x_range_3)
plot_numerical_solution(ode4, "Numerical Solution to Equation 4", y0_4, x_range_4)
plot_numerical_solution(ode7, "Numerical Solution to Equation 7", y0_7, x_range_7)
plot_numerical_solution(ode8, "Numerical Solution to Equation 8", y0_8, x_range_8)