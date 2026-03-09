import numpy as np
from sympy import*

# Из библиотеки numpy

# Создание массивов
a = np.array([1, 2, 3, 4])
print("array:", a)

b = np.zeros((2, 3))
print("zeros:\n", b)

c = np.ones((2, 3))
print("ones:\n", c)

d = np.full((2, 2), 7)
print("full:\n", d)

e = np.arange(0, 10, 2)
print("arange:", e)

f = np.linspace(0, 1, 5)
print("linspace:", f)

g = np.eye(3)
print("eye:\n", g)

h = np.random.rand(2, 2)
print("random.rand:\n", h)

i = np.random.randn(2, 2)
print("random.randn:\n", i)

# Изменение формы и размера массива
j = np.reshape(a, (2, 2))
print("reshape:\n", j)

k = np.ravel(j)
print("ravel:", k)

l = j.flatten()
print("flatten:", l)

m = np.transpose(c)
print("transpose:\n", m)

n = np.resize(a, (3, 2))
print("resize:\n", n)

# Арифметические операции
o = np.add(a, 10)
print("add:", o)

p = np.subtract(a, 1)
print("subtract:", p)

q = np.multiply(a, 2)
print("multiply:", q)

r = np.divide(a, 2)
print("divide:", r)

s = np.power(a, 2)
print("power:", s)

# Статистические функции
t = np.mean(a)
print("mean:", t)

u = np.median(a)
print("median:", u)

v = np.std(a)
print("std:", v)

w = np.var(a)
print("var:", w)

x = np.min(a)
print("min:", x)

y = np.max(a)
print("max:", y)

z = np.sum(a)
print("sum:", z)

aa = np.cumsum(a)
print("cumsum:", aa)

# Линейная алгебра
bb = np.linalg.inv(g)
print("inv:\n", bb)

cc = np.linalg.det(g)
print("det:", cc)

dd = np.linalg.eig(g)
print("eig:", dd)

ee = np.dot(g, g)
print("dot:\n", ee)

# Логические операции
ff = np.logical_and([True, False], [False, True])
print("logical_and:", ff)

gg = np.logical_or([True, False], [False, True])
print("logical_or:", gg)

hh = np.logical_not([True, False])
print("logical_not:", hh)

ii = np.where(a > 2, a, 0)
print("where:", ii)

jj = np.any(a > 2)
print("any:", jj)

kk = np.all(a > 0)
print("all:", kk)

# Сортировка и индексация
ll = np.sort(a)
print("sort:", ll)

mm = np.argsort(a)
print("argsort:", mm)

nn = np.argmax(a)
print("argmax:", nn)

oo = np.argmin(a)
print("argmin:", oo)

pp = np.nonzero(a)
print("nonzero:", pp)

qq = np.unique([1, 2, 2, 3, 3, 3])
print("unique:", qq)

# Работа с NaN и бесконечностями
rr = np.isnan([1, np.nan, 3])
print("isnan:", rr)

ss = np.isinf([1, np.inf, 3])
print("isinf:", ss)

tt = np.nan_to_num([1, np.nan, np.inf, -np.inf])
print("nan_to_num:", tt)

# Матричные операции
uu = np.matmul(g, g)
print("matmul:\n", uu)

vv = np.vdot([1, 2], [3, 4])
print("vdot:", vv)

ww = np.cross([1, 0, 0], [0, 1, 0])
print("cross:", ww)

# Пример использования tensordot с явным указанием осей
xx = np.tensordot([1, 2, 3], [4, 5, 6], axes=0)
print("tensordot (axes=0):\n", xx)

# Использование np.dot для скалярного произведения:
yy = np.dot([1, 2, 3], [4, 5, 6])
print("dot:", yy)

# Полиномы
yy = np.polyval([1, 2, 3], 4)
print("polyval:", yy)

zz = np.polyfit([0, 1, 2], [0, 1, 4], 2)
print("polyfit:", zz)

aaa = np.roots([1, -3, 2])
print("roots:", aaa)

bbb = np.polyder([1, 2, 3])
print("polyder:", bbb)

# Фурье-преобразования
ccc = np.fft.fft([1, 2, 3, 4])
print("fft:", ccc)

ddd = np.fft.ifft([1, 2, 3, 4])
print("ifft:", ddd)

eee = np.fft.fftfreq(4)
print("fftfreq:", eee)

####################################
####################################
####################################

# Из библиотеки sympy

# Инициализация символьных переменных
x, y, z = symbols('x y z')

# Операции с выражениями
expr1 = x + 2*y - 3*z
print("Expression 1:", expr1)

expr2 = expand((x + y)**3)
print("Expanded Expression:", expr2)

expr3 = factor(x**2 + 2*x*y + y**2)
print("Factored Expression:", expr3)

# Решение уравнений
eq1 = Eq(x + 2*y, 10)
solution = solve(eq1, x)
print("Solution for x:", solution)

# Дифференцирование
diff_expr = diff(x**2 + x*y + y**2, x)
print("Derivative wrt x:", diff_expr)

# Интегрирование
integral_expr = integrate(x**2 + x*y, x)
print("Integral wrt x:", integral_expr)

# Лимиты
limit_expr = limit(sin(x)/x, x, 0)
print("Limit as x approaches 0:", limit_expr)

# Ряды Тейлора
series_expr = series(exp(x), x, 0, 4)
print("Taylor Series Expansion:", series_expr)

# Решение дифференциальных уравнений
f = Function('f')
deq = Eq(f(x).diff(x, x) - 3*f(x), 0)
sol = dsolve(deq, f(x))
print("Differential Equation Solution:", sol)

# Определение матриц
A = Matrix([[1, 2], [3, 4]])
print("Matrix A:\n", A)

# Операции с матрицами
A_inv = A.inv()
print("Inverse of A:\n", A_inv)

A_det = A.det()
print("Determinant of A:", A_det)

A_eigenvals = A.eigenvals()
print("Eigenvalues of A:", A_eigenvals)

A_eigenvects = A.eigenvects()
print("Eigenvectors of A:", A_eigenvects)

# Упрощение выражений
simplified_expr = simplify(sin(x)**2 + cos(x)**2)
print("Simplified Expression:", simplified_expr)

# Замена переменных
substituted_expr = expr1.subs(x, 5)
print("Expression with x=5:", substituted_expr)

# Решение системы уравнений
eq1 = Eq(2*x + 3*y, 6)
eq2 = Eq(3*x + 2*y, 12)
solution = solve((eq1, eq2), (x, y))
print("Solution to the system of equations:", solution)

# Упрощение выражений с логарифмами и экспонентами
expr_log = log(x**2)
simplified_log_expr = simplify(expr_log)
print("Simplified Logarithm Expression:", simplified_log_expr)

expr_exp = exp(log(x))
simplified_exp_expr = simplify(expr_exp)
print("Simplified Exponential Expression:", simplified_exp_expr)
