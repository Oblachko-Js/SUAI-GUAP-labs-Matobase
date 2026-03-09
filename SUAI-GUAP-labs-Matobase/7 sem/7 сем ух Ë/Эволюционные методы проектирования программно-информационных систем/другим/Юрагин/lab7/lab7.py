# Импортируем нужные библиотеки
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.widgets import Slider, Button
import time
import warnings
warnings.filterwarnings("ignore")

# Функция Axis Parallel Hyper-ellipsoid: f(x) = sum_{i=1}^n i * x_i^2
def ellipsoid_function(x):
    n = len(x)
    return sum((i+1) * x[i]**2 for i in range(n))

# Генетический алгоритм (с записью истории для анимации)
def genetic_algorithm(n, pop_size=50, mutation_rate=0.1, max_stagnation=50, max_generations=500, save_history=False):
    bounds = (-5.12, 5.12)
    
    population = np.random.uniform(bounds[0], bounds[1], (pop_size, n))
    fitness = np.array([ellipsoid_function(ind) for ind in population])
    
    best_individual = population[np.argmin(fitness)].copy()
    best_fitness = min(fitness)
    stagnation_counter = 0
    history = []  # (population, best, best_fitness)
    
    for generation in range(max_generations):
        if save_history and n == 2:
            history.append((population.copy(), best_individual.copy(), best_fitness))
        
        # Турнирная селекция
        new_population = []
        for _ in range(pop_size):
            candidates = np.random.choice(pop_size, 3)
            winner_idx = candidates[np.argmin(fitness[candidates])]
            new_population.append(population[winner_idx])
        new_population = np.array(new_population)
        
        # Арифметический кроссовер
        for i in range(0, pop_size, 2):
            if i + 1 < pop_size:
                alpha = np.random.random()
                child1 = alpha * new_population[i] + (1 - alpha) * new_population[i+1]
                child2 = (1 - alpha) * new_population[i] + alpha * new_population[i+1]
                new_population[i] = child1
                new_population[i+1] = child2
        
        # Мутация
        for i in range(pop_size):
            if np.random.random() < mutation_rate:
                idx = np.random.randint(n)
                new_population[i, idx] += np.random.normal(0, 0.5)
                new_population[i, idx] = np.clip(new_population[i, idx], bounds[0], bounds[1])
        
        # Оценка
        new_fitness = np.array([ellipsoid_function(ind) for ind in new_population])
        
        # Элитизм
        best_idx = np.argmin(new_fitness)
        if new_fitness[best_idx] < best_fitness:
            best_individual = new_population[best_idx].copy()
            best_fitness = new_fitness[best_idx]
            stagnation_counter = 0
        else:
            stagnation_counter += 1
        
        population = new_population
        fitness = new_fitness
        
        if stagnation_counter >= max_stagnation or best_fitness < 1e-8:
            break
    
    if save_history and n == 2:
        history.append((population.copy(), best_individual.copy(), best_fitness))
    
    return best_individual, best_fitness, generation + 1, history

def plot_ellipsoid_interactive():
    print("Запускаю ГА для n=2 с сохранением истории")
    best_ind, best_fit, gens, history = genetic_algorithm(
        n=2, pop_size=70, mutation_rate=0.15, max_stagnation=40, save_history=True
    )
    print(f"Готово! Найден минимум: f({best_ind}) = {best_fit:.2e} за {gens} поколений")

    fig = plt.figure(figsize=(13, 9))
    ax = fig.add_subplot(111, projection='3d')

    # Поверхность функции
    x = np.linspace(-5.12, 5.12, 100)
    y = np.linspace(-5.12, 5.12, 100)
    X, Y = np.meshgrid(x, y)
    Z = X**2 + 2*Y**2
    ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.5, linewidth=0, antialiased=True)

    # Начальные точки
    pop_scatter = ax.scatter([], [], [], c='black', s=30, alpha=0.8)
    best_scatter = ax.scatter([], [], [], c='red', s=200, marker='*')

    ax.set_xlim(-5.12, 5.12)
    ax.set_ylim(-5.12, 5.12)
    ax.set_zlim(0, 150)
    ax.set_xlabel('x1')
    ax.set_ylabel('x2')
    ax.set_zlabel('f(x)')
    ax.set_title('Axis Parallel Hyper-ellipsoid (n=2)')

    # Ползунок
    ax_slider = plt.axes([0.15, 0.9, 0.7, 0.03])
    slider = Slider(ax_slider, 'Поколение', 0, len(history)-1, valinit=len(history)-1, valstep=1)

    # Обновление графика
    def update(frame):
        frame = int(frame)
        pop, best, fit = history[frame]
        
        ax.cla()
        ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.5, linewidth=0, antialiased=True)
        
        zs_pop = [ellipsoid_function(p) for p in pop]
        ax.scatter(pop[:,0], pop[:,1], zs_pop, c='black', s=30, alpha=0.8, label='Популяция')
        ax.scatter(best[0], best[1], ellipsoid_function(best), c='red', s=200, marker='*', label=f'Лучший: {fit:.2e}')
        
        ax.set_xlim(-5.12, 5.12)
        ax.set_ylim(-5.12, 5.12)
        ax.set_zlim(0, 150)
        ax.set_title(f'ГА: Поколение {frame}/{len(history)-1} | f(x) = {fit:.2e} | Всего поколений: {gens}')
        ax.legend(loc='upper left')

    slider.on_changed(update)
    update(len(history)-1)  # Показать финал сразу

    # Кнопки
    ax_prev = plt.axes([0.05, 0.9, 0.1, 0.05])
    ax_next = plt.axes([0.86, 0.9, 0.1, 0.05])
    btn_prev = Button(ax_prev, 'Пред.', color='lightcoral')
    btn_next = Button(ax_next, 'След. ►', color='lightgreen')

    def prev(event): 
        val = max(0, slider.val - 1)
        slider.set_val(val)
    def next(event): 
        val = min(len(history)-1, slider.val + 1)
        slider.set_val(val)

    btn_prev.on_clicked(prev)
    btn_next.on_clicked(next)

    # Клавиши ← →
    def on_key(event):
        if event.key == 'left': prev(None)
        if event.key == 'right': next(None)
    fig.canvas.mpl_connect('key_press_event', on_key)

    plt.subplots_adjust(bottom=0.15)
    plt.show()

# Исследование зависимости от параметров
def research():
    dimensions = [2, 3, 5, 10]
    pop_sizes = [20, 50, 100]
    mut_rates = [0.01, 0.1, 0.2]
    
    print("\n# ИССЛЕДОВАНИЕ ПАРАМЕТРОВ")
    print("# n | популяция | мутация | fitness      | поколений | время(с)")
    print("-" * 70)
    
    for n in dimensions:
        for pop in pop_sizes:
            for mut in mut_rates:
                start = time.time()
                best_ind, best_fit, gens, _ = genetic_algorithm(
                    n=n, pop_size=pop, mutation_rate=mut, max_stagnation=50
                )
                t = time.time() - start
                
                print(f"{n:2d} | {pop:3d}     | {mut:.2f}    | {best_fit:.2e} | {gens:4d}     | {t:.3f}")

# ЗАПУСК
if __name__ == "__main__":
    plot_ellipsoid_interactive()   # ИНТЕРАКТИВНЫЙ ГРАФИК С ПОЛЗУНКОМ!
    research()                     # ТАБЛИЦА ИССЛЕДОВАНИЯ