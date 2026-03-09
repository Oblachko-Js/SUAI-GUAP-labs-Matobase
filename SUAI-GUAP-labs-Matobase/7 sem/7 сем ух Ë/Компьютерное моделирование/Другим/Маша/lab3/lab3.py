import numpy as np
import matplotlib.pyplot as plt

# Исходные данные (ВАРИАНТ 7) — потребление мяса птицы в Африке, кг/чел/год
x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])       # 2000 → 1, 2001 → 2, ..., 2009 → 10
y = np.array([4.2, 4.3, 4.5, 4.7, 4.6, 4.7, 4.8, 5.2, 5.4, 5.5])
n = len(y)

# Функция для расчета R²
def calculate_r2(y_true, y_pred):
    sse = np.sum((y_true - y_pred) ** 2)
    sst = np.sum((y_true - np.mean(y_true)) ** 2)
    r2 = 1 - sse / sst if sst != 0 else 0
    return r2

# Функция для расчета R_adj² (k — число параметров)
def calculate_adj_r2(y_true, y_pred, n, k):
    r2 = calculate_r2(y_true, y_pred)
    adj_r2 = 1 - (1 - r2) * (n - 1) / (n - k) if (n - k) > 0 else -np.inf
    return adj_r2

# a. Самостоятельная реализация МНК для полинома 2-й степени
X = np.vstack([x**2, x, np.ones(n)]).T
coef1 = np.linalg.lstsq(X, y, rcond=None)[0]
a2, a1, a0 = coef1
y_pred1 = a2 * x**2 + a1 * x + a0
r2_1 = calculate_r2(y, y_pred1)
adj_r2_1 = calculate_adj_r2(y, y_pred1, n, 3)  # k=3 (a0, a1, a2)

# Прогноз для x=11 (2010 год) по модели f1(x)
y_pred1_x11 = a2 * (11**2) + a1 * 11 + a0

# b. Встроенная реализация для полиномов степени p ≠ 2
degrees = [1, 3, 4, 5, 6, 7]
adj_r2_list = []
best_p = None
best_adj_r2 = -np.inf
best_coef = None
best_y_pred = None
plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Исходные данные')
for p in degrees:
    coef = np.polyfit(x, y, p)
    y_pred = np.polyval(coef, x)
    r2 = calculate_r2(y, y_pred)
    adj_r2 = calculate_adj_r2(y, y_pred, n, p + 1)  # k = p + 1
    adj_r2_list.append((p, adj_r2))
    plt.plot(x, y_pred, label=f'Полином степени {p} (R_adj²={adj_r2:.3f})')
    if adj_r2 > best_adj_r2:
        best_adj_r2 = adj_r2
        best_p = p
        best_coef = coef
        best_y_pred = y_pred
plt.legend()
plt.title('Аппроксимация полиномами разных степеней')
plt.xlabel('x (годы, 1=2000, 10=2009)')
plt.ylabel('Y (кг/чел/год)')
plt.grid(True)
plt.show()

# Прогноз для x=11 (2010 год) по модели f2(x)
y_pred2_x11 = np.polyval(best_coef, 11)

# c. Аппроксимация моделью f3(x) = ∛(x + 1) + 1
y_pred3 = (x + 1) ** (1/3) + 1
r2_3 = calculate_r2(y, y_pred3)
adj_r2_3 = calculate_adj_r2(y, y_pred3, n, 0)  # k=0 (фиксированная модель)
print("=== Результаты аппроксимации моделью f3(x) ===")
print(f"Предсказанные значения y_pred3: {y_pred3}")
print(f"Коэффициент детерминации R²: {r2_3:.6f}")
print(f"Скорректированный R_adj²: {adj_r2_3:.6f}")

# Прогноз для x=11 (2010 год) по модели f3(x)
y_pred3_x11 = (11 + 1) ** (1/3) + 1

# d. Сравнение по R_adj²
adj_r2_f1 = adj_r2_1
adj_r2_f2 = best_adj_r2
adj_r2_f3 = adj_r2_3
print("\n=== Сравнение моделей по R_adj² ===")
print(f"Модель f1(x) (полином 2-й степени): R_adj² = {adj_r2_f1:.6f}")
print(f"Модель f2(x) (лучший полином степени {best_p}): R_adj² = {adj_r2_f2:.6f}")
print(f"Модель f3(x) (∛(x + 1) + 1): R_adj² = {adj_r2_f3:.6f}")

# Прогноз на 2010 год (x=11)
print("\n=== Прогноз на 2010 год (x=11) ===")
print(f"Модель f1(x): {y_pred1_x11:.3f} кг/чел/год")
print(f"Модель f2(x) (степень {best_p}): {y_pred2_x11:.3f} кг/чел/год")
print(f"Модель f3(x): {y_pred3_x11:.3f} кг/чел/год")