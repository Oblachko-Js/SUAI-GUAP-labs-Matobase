import pulp

# Создаём модель для минимизации отходов
model = pulp.LpProblem("Минимизация_отходов_фанеры", pulp.LpMinimize)

# Переменные: количество листов по каждому способу (целочисленные)
x1 = pulp.LpVariable('x1', lowBound=0, cat='Integer')  # Способ 1
x2 = pulp.LpVariable('x2', lowBound=0, cat='Integer')  # Способ 2

# Целевая функция: минимизация отходов (12*x1 + 16*x2)
model += 12 * x1 + 16 * x2, "Общие_отходы"

# Ограничения на производство заготовок
model += 2 * x1 + 6 * x2 >= 24, "Заготовки_I"  # Минимум 24 шт. I
model += 5 * x1 + 4 * x2 >= 31, "Заготовки_II"  # Минимум 31 шт. II
model += 2 * x1 + 3 * x2 >= 18, "Заготовки_III"  # Минимум 18 шт. III

# Решаем задачу
model.solve()

# Вывод результатов
print(f"Статус решения: {pulp.LpStatus[model.status]}")
print(f"Оптимальное количество листов по способу 1 (x1): {pulp.value(x1)}")
print(f"Оптимальное количество листов по способу 2 (x2): {pulp.value(x2)}")
print(f"Минимальные отходы: {pulp.value(model.objective)} см²")

# Проверка производства
print(f"Произведено заготовок I: {2 * pulp.value(x1) + 6 * pulp.value(x2)} шт.")
print(f"Произведено заготовок II: {5 * pulp.value(x1) + 4 * pulp.value(x2)} шт.")
print(f"Произведено заготовок III: {2 * pulp.value(x1) + 3 * pulp.value(x2)} шт.")