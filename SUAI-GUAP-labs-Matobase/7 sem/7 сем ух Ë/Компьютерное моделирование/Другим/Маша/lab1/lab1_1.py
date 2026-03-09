import pulp

# Создаём модель для минимизации затрат
model = pulp.LpProblem("Минимизация_затрат_сплава", pulp.LpMinimize)

# Переменные: количество смесей №1 и №2 (целочисленные)
x1 = pulp.LpVariable('x1', lowBound=0, cat='Integer')  # Смесь №1
x2 = pulp.LpVariable('x2', lowBound=0, cat='Integer')  # Смесь №2

# Целевая функция: минимизация затрат (40*x1 + 60*x2)
model += 40 * x1 + 60 * x2, "Общие_затраты"

# Ограничения
model += 0.1 * x1 + 0.1 * x2 <= 2, "Максимум_меди"  # Не более 2 кг меди
model += 0.1 * x1 + 0.3 * x2 >= 3, "Минимум_олова"  # Не менее 3 кг олова
model += 0.8 * x1 + 0.6 * x2 >= 7.2, "Минимум_цинка"  # Не менее 7.2 кг цинка
model += 0.8 * x1 + 0.6 * x2 <= 12.8, "Максимум_цинка"  # Не более 12.8 кг цинка

# Решаем задачу
model.solve()

# Вывод результатов
print(f"Статус решения: {pulp.LpStatus[model.status]}")
print(f"Количество смесей №1 (x1): {pulp.value(x1)}")
print(f"Количество смесей №2 (x2): {pulp.value(x2)}")
print(f"Минимальные затраты: {pulp.value(model.objective)} руб.")

# Проверка состава сплава
med = 0.1 * pulp.value(x1) + 0.1 * pulp.value(x2)  # Медь
olov = 0.1 * pulp.value(x1) + 0.3 * pulp.value(x2)  # Олово
cink = 0.8 * pulp.value(x1) + 0.6 * pulp.value(x2)  # Цинк
print(f"Содержание меди: {med} кг")
print(f"Содержание олова: {olov} кг")
print(f"Содержание цинка: {cink} кг")