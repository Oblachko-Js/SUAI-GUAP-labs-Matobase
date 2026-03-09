from scipy.optimize import differential_evolution

# Функция уже есть, но для ясно
def moved_hyper_ellipsoid(x):
    n = len(x)
    return sum(5**i * x[i-1]**2 for i in range(1, n+1))

# Для n=2: Стандартный toolbox (differential_evolution как аналог GA Toolbox)
bounds_de = [(-5.12, 5.12)] * 2
res_de = differential_evolution(moved_hyper_ellipsoid, bounds_de, maxiter=100, popsize=15, seed=42)  # seed для воспроизводимости

print("=== Сравнение результатов (n=2) ===")
print(f"Твой GA: Best x = {best_x}, Best f = {best_f:.6f}, Generations = {gens}")
print(f"Toolbox (DE): Best x = {res_de.x}, Best f = {res_de.fun:.6f}, Evaluations = {res_de.nfev}")
print(f"Сравнение: DE точнее ({res_de.fun} vs {best_f}), но GA использует {gens} поколений vs ~{res_de.nfev / 15} итераций DE (popsize=15).")
