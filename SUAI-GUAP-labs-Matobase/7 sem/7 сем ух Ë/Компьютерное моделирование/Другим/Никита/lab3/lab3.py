import numpy as np
import matplotlib.pyplot as plt

# Данные Вариант 25 (первые 7 месяцев 2017 г., млн т стали)
t = np.array([1, 2, 3, 4, 5, 6, 7])
Y = np.array([138, 127, 143, 142, 145, 143, 146])
n = len(Y)

# Функции для R² и скорректированного R²
def calculate_r2(y_true, y_pred):
    sse = np.sum((y_true - y_pred) ** 2)
    sst = np.sum((y_true - np.mean(y_true)) ** 2)
    return 1 - sse / sst if sst != 0 else 0

def calculate_adj_r2(y_true, y_pred, n, k):
    r2 = calculate_r2(y_true, y_pred)
    return 1 - (1 - r2) * (n - 1) / (n - k) if (n - k) > 0 else -np.inf

# a) МНК для полинома 2-й степени (самостоятельная реализация)
X = np.vstack([t**2, t, np.ones(n)]).T
coef1 = np.linalg.lstsq(X, Y, rcond=None)[0]
a2, a1, a0 = coef1
Y_pred1 = a2 * t**2 + a1 * t + a0

r2_1 = calculate_r2(Y, Y_pred1)
adj_r2_1 = calculate_adj_r2(Y, Y_pred1, n, 3)        # k = 3 параметра

# Прогноз на 8-й месяц (t=8)
Y_pred1_t8 = a2 * 64 + a1 * 8 + a0

# b) Перебор полиномов разных степеней (1–6, т.к. n=7 → максимум степень 6)
degrees = [1, 2, 3, 4, 5, 6]
best_adj_r2 = -np.inf
best_p = None
best_coef = None

plt.figure(figsize=(10, 6))
plt.scatter(t, Y, color='black', label='Исходные данные')
for p in degrees:
    coef = np.polyfit(t, Y, p)
    Y_pred = np.polyval(coef, t)
    adj_r2 = calculate_adj_r2(Y, Y_pred, n, p + 1)
    
    t_fine = np.linspace(1, 8, 200)
    plt.plot(t_fine, np.polyval(coef, t_fine), label=f'степень {p} (R_adj²={adj_r2:.4f})')
    
    if adj_r2 > best_adj_r2:
        best_adj_r2 = adj_r2
        best_p = p
        best_coef = coef

plt.legend()
plt.title('Аппроксимация производства стали полиномами разных степеней')
plt.xlabel('Месяц (t = 1..7 — январь–июль 2017)')
plt.ylabel('Объём производства, млн т')
plt.grid(True)
plt.show()

# Прогноз на 8-й месяц по лучшему полиному
Y_pred2_t8 = np.polyval(best_coef, 8)

# c) Сравнение всех моделей
print("=== Результаты ===")
print(f"Полином 2-й степени (f1):        R_adj² = {adj_r2_1:.5f}  →  прогноз на 8-й месяц: {Y_pred1_t8:.3f} млн т")
print(f"Лучший полином степени {best_p} (f2): R_adj² = {best_adj_r2:.5f}  →  прогноз: {Y_pred2_t8:.3f} млн т")

print("\nПолная таблица R_adj² для всех полиномов:")
for p in degrees:
    coef = np.polyfit(t, Y, p)
    adj = calculate_adj_r2(Y, np.polyval(coef, t), n, p+1)
    print(f"Степень {p:1d} → R_adj² = {adj:.5f}")

# Вывод итоговой рекомендации
print("\nРекомендуемая модель — полином степени", best_p if best_adj_r2 > adj_r2_1 else 2)
print(f"Прогноз производства стали на август 2017 (t=8): {max(Y_pred1_t8, Y_pred2_t8):.3f} млн тонн")