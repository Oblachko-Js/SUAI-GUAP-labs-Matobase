import random
import matplotlib.pyplot as plt
import time

# =============================================
# ЛАБОРАТОРНАЯ РАБОТА №3
# ВАРИАНТ 6 — Перестановочное кодирование
# Расширенное исследование параметров ГА
# =============================================

# Простая задача — набор 6
CAPACITY_SIMPLE = 170
WEIGHTS_SIMPLE = [41, 50, 49, 59, 55, 57, 60]
PROFITS_SIMPLE = [442, 525, 511, 593, 546, 564, 617]
OPTIMAL_SIMPLE = 1735

# Сложная задача — набор 5, n=51
CAPACITY_COMPLEX = 11922
WEIGHTS_COMPLEX = [338,310,819,481,316,482,705,58,976,23,750,845,19,788,367,579,10,47,181,956,
                   197,756,930,943,345,355,525,776,109,749,798,798,860,37,946,92,341,611,919,
                   340,925,546,313,317,178,79,149,690,997,162,49]

PROFITS_COMPLEX = [623,742,796,943,740,923,30,466,944,649,901,114,470,247,544,574,14,217,280,917,
                   766,160,798,139,618,127,2,872,210,216,983,873,290,962,540,678,205,941,691,
                   967,894,299,362,166,146,66,302,604,4,678,500]  # 51 элемент

class KnapsackGA_Permutation:
    def __init__(self, capacity, weights, profits, pop_size=120, generations=400,
                 crossover_prob=0.8, mutation_prob=0.1, seed=None):
        if seed is not None:
            random.seed(seed)
        self.capacity = capacity
        self.weights = weights
        self.profits = profits
        self.n = len(weights)
        self.pop_size = pop_size
        self.generations = generations
        self.crossover_prob = crossover_prob
        self.mutation_prob = mutation_prob

        self.population = [list(range(self.n)) for _ in range(pop_size)]
        for ind in self.population:
            random.shuffle(ind)
        self.history = []

    def decode_and_fitness(self, perm):
        weight = profit = 0
        for idx in perm:
            if weight + self.weights[idx] <= self.capacity:
                weight += self.weights[idx]
                profit += self.profits[idx]
        return profit, weight

    def fitness(self, perm):
        return self.decode_and_fitness(perm)[0]

    def order_crossover(self, p1, p2):
        if random.random() > self.crossover_prob:
            return p1[:], p2[:]
        start, end = sorted(random.sample(range(self.n), 2))
        child1, child2 = [None] * self.n, [None] * self.n
        child1[start:end] = p1[start:end]
        child2[start:end] = p2[start:end]
        p2_rest = [x for x in p2 if x not in p1[start:end]]
        p1_rest = [x for x in p1 if x not in p2[start:end]]
        for i in range(self.n):
            if child1[i] is None:
                child1[i] = p2_rest.pop(0)
            if child2[i] is None:
                child2[i] = p1_rest.pop(0)
        return child1, child2

    def mutate(self, ind):
        if random.random() < self.mutation_prob:
            i, j = random.sample(range(self.n), 2)
            ind[i], ind[j] = ind[j], ind[i]
        return ind

    def run(self):
        best_ever = 0
        best_perm = None
        for gen in range(self.generations):
            fitnesses = [self.fitness(ind) for ind in self.population]
            best_idx = fitnesses.index(max(fitnesses))
            if fitnesses[best_idx] > best_ever:
                best_ever = fitnesses[best_idx]
                best_perm = self.population[best_idx][:]
            self.history.append(best_ever)

            new_pop = [self.population[best_idx][:]]
            while len(new_pop) < self.pop_size:
                p1 = max(random.sample(self.population, 3), key=self.fitness)
                p2 = max(random.sample(self.population, 3), key=self.fitness)
                c1, c2 = self.order_crossover(p1, p2)
                new_pop.append(self.mutate(c1))
                if len(new_pop) < self.pop_size:
                    new_pop.append(self.mutate(c2))
            self.population = new_pop

        # Финальное декодирование
        weight = profit = 0
        for idx in best_perm:
            if weight + self.weights[idx] <= self.capacity:
                weight += self.weights[idx]
                profit += self.profits[idx]
        return profit, weight, self.history


# =============================================
# ОСНОВНОЙ ЗАПУСК — ПО ПУНКТАМ
# =============================================

if __name__ == "__main__":
    # =============================================
    # 1. Решение простой задачи
    # =============================================
    print("1. РЕШЕНИЕ ПРОСТОЙ ЗАДАЧИ (набор 6)")
    print("-" * 70)
    ga = KnapsackGA_Permutation(CAPACITY_SIMPLE, WEIGHTS_SIMPLE, PROFITS_SIMPLE,
                                pop_size=150, generations=500, crossover_prob=0.9,
                                mutation_prob=0.15, seed=777)
    profit, weight, hist = ga.run()
    print(f"   → Найденная стоимость: {profit} → {'ОПТИМУМ ДОСТИГНУТ ✓' if profit == 1735 else 'НЕ ДОСТИГНУТ ✗'}")
    print(f"   → Вес: {weight}/170\n")

    plt.figure(figsize=(10, 6))
    plt.plot(hist, color="teal", linewidth=2.5)
    plt.axhline(1735, color="red", linestyle="--", label="Оптимум = 1735")
    plt.title("1. Сходимость — простая задача")
    plt.xlabel("Поколение")
    plt.ylabel("Стоимость")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

    # =============================================
    # 2. Влияние вероятности скрещивания
    # =============================================
    print("2. ИССЛЕДОВАНИЕ ВЕРОЯТНОСТИ СКРЕЩИВАНИЯ (p_c)")
    print("-" * 70)
    probs = [0.6, 0.7, 0.8, 0.9, 0.95]
    plt.figure(figsize=(12, 8))
    for p in probs:
        print(f"   p_c = {p} ...", end=" ")
        ga = KnapsackGA_Permutation(CAPACITY_SIMPLE, WEIGHTS_SIMPLE, PROFITS_SIMPLE,
                                    pop_size=150, generations=500, crossover_prob=p,
                                    mutation_prob=0.15, seed=42)
        start = time.time()
        profit, _, hist = ga.run()
        t = time.time() - start
        print(f"→ {profit} ({'оптимум' if profit == 1735 else profit}) за {t:.2f}с")
        plt.plot(hist, label=f"p_c={p} → {profit}", linewidth=2)
    plt.axhline(1735, color='red', linestyle='--', label='Оптимум 1735')
    plt.title("2. Влияние вероятности скрещивания")
    plt.xlabel("Поколение")
    plt.ylabel("Лучшая стоимость")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.show()

    # =============================================
    # 3. Влияние вероятности мутации
    # =============================================
    print("\n3. ИССЛЕДОВАНИЕ ВЕРОЯТНОСТИ МУТАЦИИ (p_m)")
    print("-" * 70)
    mut_probs = [0.01, 0.05, 0.1, 0.15, 0.2, 0.3]
    plt.figure(figsize=(12, 8))
    for pm in mut_probs:
        print(f"   p_m = {pm} ...", end=" ")
        ga = KnapsackGA_Permutation(CAPACITY_SIMPLE, WEIGHTS_SIMPLE, PROFITS_SIMPLE,
                                    pop_size=150, generations=500, crossover_prob=0.9,
                                    mutation_prob=pm, seed=42)
        start = time.time()
        profit, _, hist = ga.run()
        t = time.time() - start
        print(f"→ {profit} ({'оптимум' if profit == 1735 else profit}) за {t:.2f}с")
        plt.plot(hist, label=f"p_m={pm} → {profit}", linewidth=2)
    plt.axhline(1735, color='red', linestyle='--', label='Оптимум 1735')
    plt.title("3. Влияние вероятности мутации")
    plt.xlabel("Поколение")
    plt.ylabel("Лучшая стоимость")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.show()

    # =============================================
    # 4. Влияние размера популяции
    # =============================================
    print("\n4. ИССЛЕДОВАНИЕ РАЗМЕРА ПОПУЛЯЦИИ")
    print("-" * 70)
    pop_sizes = [50, 100, 150, 200, 300, 400]
    plt.figure(figsize=(12, 8))
    for size in pop_sizes:
        print(f"   pop_size = {size} ...", end=" ")
        ga = KnapsackGA_Permutation(CAPACITY_SIMPLE, WEIGHTS_SIMPLE, PROFITS_SIMPLE,
                                    pop_size=size, generations=500, crossover_prob=0.9,
                                    mutation_prob=0.15, seed=42)
        start = time.time()
        profit, _, hist = ga.run()
        t = time.time() - start
        print(f"→ {profit} ({'оптимум' if profit == 1735 else profit}) за {t:.2f}с")
        plt.plot(hist, label=f"pop={size} → {profit}", linewidth=2)
    plt.axhline(1735, color='red', linestyle='--', label='Оптимум 1735')
    plt.title("4. Влияние размера популяции")
    plt.xlabel("Поколение")
    plt.ylabel("Лучшая стоимость")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.show()

    # =============================================
    # 5. Решение сложной задачи
    # =============================================
    print("\n5. РЕШЕНИЕ СЛОЖНОЙ ЗАДАЧИ (n=51)")
    print("-" * 70)
    ga_big = KnapsackGA_Permutation(CAPACITY_COMPLEX, WEIGHTS_COMPLEX, PROFITS_COMPLEX,
                                     pop_size=400, generations=800,
                                     crossover_prob=0.92, mutation_prob=0.18, seed=123)
    profit_big, weight_big, hist_big = ga_big.run()
    fill = weight_big / CAPACITY_COMPLEX * 100
    print(f"   → Найденная стоимость: {profit_big}")
    print(f"   → Заполнение рюкзака: {weight_big}/{CAPACITY_COMPLEX} ({fill:.2f}%)")

    plt.figure(figsize=(10, 6))
    plt.plot(hist_big, color="darkorange", linewidth=2.5)
    plt.title("5. Сходимость — сложная задача (n=51)")
    plt.xlabel("Поколение")
    plt.ylabel("Стоимость")
    plt.grid(alpha=0.3)
    plt.show()