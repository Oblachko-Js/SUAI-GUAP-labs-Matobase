import pulp

# Создаём модель для минимизации отходов
model = pulp.LpProblem("Минимизация_отходов_фанеры", pulp.LpMinimize)

# Переменные: количество листов по каждому способу (целочисленные)
x1 = pulp.LpVariable('x1', lowBound=0, cat='Integer')  # Способ 1
x2 = pulp.LpVariable('x2', lowBound=0, cat='Integer')  # Способ 2

# Целевая функция: минимизация отходов (6*x1 + 4*x2)
model += 6 * x1 + 4 * x2, "Общие_отходы"

# Ограничения
model += x1 + x2 == 5000, "Всего_листов"  # 5000 листов
model += (2 * x1 + x2) >= (2 * x1 + 4 * x2), "Детали_А_не_меньше_Б"  # a >= b

# Решаем задачу
model.solve()

# Вывод результатов
print(f"Статус решения: {pulp.LpStatus[model.status]}")
print(f"Листов по способу 1 (x1): {pulp.value(x1)}")
print(f"Листов по способу 2 (x2): {pulp.value(x2)}")
print(f"Минимальные отходы: {pulp.value(model.objective)} м²")

# Проверка производства
a = 2 * pulp.value(x1) + pulp.value(x2)  # Детали А
b = 2 * pulp.value(x1) + 4 * pulp.value(x2)  # Детали Б
print(f"Деталей А: {a} шт.")
print(f"Деталей Б: {b} шт.")
print(f"Условие А >= Б: {a >= b}")