import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import differential_evolution
import time

# Определение целевой функции
def fitness(x):
    return np.sin(2 * x) / (x ** 2) if x != 0 else float('inf')

# Класс генетического алгоритм
class GeneticAlgorithm:
    def __init__(self, pop_size, p_cross, p_mut, max_gen, bounds, elitism=True, patience=10, epsilon=1e-6):
        self.pop_size = pop_size
        self.p_cross = p_cross
        self.p_mut = p_mut
        self.max_gen = max_gen
        self.bounds = bounds
        self.elitism = elitism
        self.patience = patience
        self.epsilon = epsilon
        self.population = np.random.uniform(bounds[0], bounds[1], pop_size)
        self.best_history = []
        plt.ion()
        self.fig, self.ax = plt.subplots()

    def evaluate_fitness(self):
        return np.array([fitness(x) for x in self.population])

    def select_parents(self):
        fitnesses = self.evaluate_fitness()
        idx = np.argsort(fitnesses)[-3:]
        return self.population[idx[-1]], self.population[idx[-2]]

    def crossover(self, p1, p2):
        if np.random.rand() < self.p_cross:
            scale = 1700 / (self.bounds[1] - self.bounds[0])
            b1 = format(int((p1 - self.bounds[0]) * scale), '015b')
            b2 = format(int((p2 - self.bounds[0]) * scale), '015b')
            point = np.random.randint(1, 15)
            child_bits = b1[:point] + b2[point:]
            child = self.bounds[0] + (int(child_bits, 2) / scale)
            return np.clip(child, self.bounds[0], self.bounds[1])
        return p1 if np.random.rand() < 0.5 else p2

    def mutate(self, ind):
        if np.random.rand() < self.p_mut:
            scale = 1700 / (self.bounds[1] - self.bounds[0])
            binary = format(int((ind - self.bounds[0]) * scale), '015b')
            pos = np.random.randint(0, 15)
            bits = list(binary)
            bits[pos] = '1' if bits[pos] == '0' else '0'
            child = self.bounds[0] + (int(''.join(bits), 2) / scale)
            return np.clip(child, self.bounds[0], self.bounds[1])
        return ind

    def run(self):
        best_f = -np.inf
        no_improve = 0
        for gen in range(self.max_gen):
            fits = self.evaluate_fitness()
            best_idx = np.argmax(fits)
            current_best_x = self.population[best_idx]
            current_best_f = fits[best_idx]
            self.best_history.append((gen, current_best_x, current_best_f))

            if current_best_f > best_f + self.epsilon:
                best_f = current_best_f
                no_improve = 0
            else:
                no_improve += 1
            if no_improve >= self.patience:
                break

            new_pop = [current_best_x] if self.elitism else []
            while len(new_pop) < self.pop_size:
                p1, p2 = self.select_parents()
                child = self.crossover(p1, p2)
                child = self.mutate(child)
                new_pop.append(child)
            self.population = np.array(new_pop[:self.pop_size])

            self.plot_function_with_best(gen, current_best_x)
            print(f"Поколение {gen + 1}: x = {current_best_x:.4f}, f(x) = {current_best_f:.6f}")

        plt.ioff()
        return current_best_x, current_best_f, gen + 1

    def plot_function_with_best(self, gen, best_x):
        self.ax.cla()
        x_vals = np.linspace(self.bounds[0], self.bounds[1], 1000)
        y_vals = [fitness(x) for x in x_vals]
        self.ax.plot(x_vals, y_vals, label='$f(x) = \\frac{\\sin(2x)}{x^2}$')
        self.ax.scatter([best_x], [fitness(best_x)], color='red', label='Текущий максимум')
        self.ax.set_title(f'Поколение {gen + 1}')
        self.ax.set_xlabel('x')
        self.ax.set_ylabel('f(x)')
        self.ax.legend()
        self.ax.grid()
        self.ax.set_xlim(self.bounds[0], self.bounds[1])
        plt.draw()
        plt.pause(0.1)

# Нахождение истинного максимума
def neg_f(x):
    return -fitness(x[0])

bounds_opt = [(-20, -3.1)]
result = differential_evolution(neg_f, bounds_opt)
true_x = result.x[0]
true_f = -result.fun

# Эксперименты
bounds = (-20, -3.1)
params = [(5, 0.7, 0.01), (50, 0.8, 0.05), (100, 0.9, 0.1)]
results = []
for pop_size, p_cross, p_mut in params:
    ga = GeneticAlgorithm(pop_size, p_cross, p_mut, max_gen=200, bounds=bounds)
    start_time = time.time()
    best_x, best_f, gens = ga.run()
    time_taken = time.time() - start_time
    acc_x = abs(best_x - true_x)
    acc_f = abs(best_f - true_f)
    results.append([pop_size, p_cross, p_mut, gens, time_taken, acc_x, acc_f])

# Вывод результатов
print("Параметры (Pop, Pc, Pm) | Поколения | Время (с) | Точность x | Точность f")
for r in results:
    print(f"{r[0]}, {r[1]:.1f}, {r[2]:.2f} | {r[3]} | {r[4]:.2f} | {r[5]:.4f} | {r[6]:.6f}")
print(f"Истинный максимум: x = {true_x:.4f}, f(x) = {true_f:.6f}")
plt.show()
