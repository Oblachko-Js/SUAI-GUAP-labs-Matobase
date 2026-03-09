import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
import time
from itertools import product

# Функция цели
def objective(x):
    n = len(x)
    return sum((i+1) * x[i]**2 for i in range(n))   

bounds = (-5.12, 5.12)

# Эволюционная стратегия (μ + λ)-ES
class EvolutionStrategy:
    def __init__(self, n_dim, mu=20, lambda_=100, max_stagnation=50, max_generations=500):
        self.n = n_dim
        self.mu = mu
        self.lambda_ = lambda_
        self.max_stagnation = max_stagnation
        self.max_generations = max_generations

        self.parents = np.random.uniform(bounds[0], bounds[1], (mu, n_dim))
        self.parent_sigmas = np.full((mu, n_dim), 1.0)
        self.parent_fitness = np.array([objective(ind) for ind in self.parents])

        self.history = []
        self.best_solution = None
        self.best_fitness = np.inf
        self.generation = 0
        self.stagnation_counter = 0

    def mutate(self, ind, sigma):
        child = ind + np.random.normal(0, sigma, len(ind))
        child = np.clip(child, bounds[0], bounds[1])
        sigma_new = sigma * np.exp(0.2 * np.random.randn(len(sigma)))
        sigma_new = np.clip(sigma_new, 0.01, 3.0)
        return child, sigma_new

    def step(self):
        offspring = []
        offspring_sigmas = []

        for _ in range(self.lambda_):
            idx = np.random.randint(0, self.mu)
            child, sigma = self.mutate(self.parents[idx], self.parent_sigmas[idx])
            offspring.append(child)
            offspring_sigmas.append(sigma)

        offspring = np.array(offspring)
        offspring_sigmas = np.array(offspring_sigmas)
        offspring_fitness = np.array([objective(ind) for ind in offspring])

        # (μ + λ) отбор
        combined = np.vstack((self.parents, offspring))
        combined_sigmas = np.vstack((self.parent_sigmas, offspring_sigmas))
        combined_fitness = np.hstack((self.parent_fitness, offspring_fitness))

        idx = np.argsort(combined_fitness)[:self.mu]
        self.parents = combined[idx]
        self.parent_sigmas = combined_sigmas[idx]
        self.parent_fitness = combined_fitness[idx]

        best_fit = self.parent_fitness[0]
        best_sol = self.parents[0].copy()

        self.history.append({
            'parents': self.parents.copy(),
            'best': best_sol,
            'fitness': best_fit,
            'gen': self.generation
        })

        if best_fit < self.best_fitness:
            self.best_fitness = best_fit
            self.best_solution = best_sol.copy()
            self.stagnation_counter = 0
        else:
            self.stagnation_counter += 1

        self.generation += 1
        return (self.stagnation_counter >= self.max_stagnation or
                self.generation >= self.max_generations)

    def run(self):
        start = time.time()
        while not self.step():
            pass
        return time.time() - start


# 3D анимация + переключение стрелками
def animate_3d(n_dim=2, mu=20, lambda_=100):
    es = EvolutionStrategy(n_dim=n_dim, mu=mu, lambda_=lambda_, max_stagnation=30)
    print(f"\nЗапуск ЭС для n={n_dim}...")
    es.run()

    x = np.linspace(bounds[0], bounds[1], 100)
    current_frame = [0]  
    ani = [None]  
    paused = [False] 

    # --- n=3 (проекция на x1, x2) ---
    if n_dim == 3:
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        X, Y = np.meshgrid(x, x)
        Z = 1*X**2 + 2*Y**2
        ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.5, linewidth=0, antialiased=True)
        ax.set_xlabel('x₁')
        ax.set_ylabel('x₂')
        ax.set_zlabel('f(x₁,x₂,0)')
        ax.set_title('Axis Parallel Hyper-Ellipsoid (n=3), x₃=0')

        scatter = ax.scatter([], [], [], c='red', s=30, label='Популяция')
        best_point = ax.scatter([], [], [], c='yellow', s=100, marker='*', label='Лучший')

        def update(frame):
            data = es.history[frame]
            parents = data['parents']
            x1, x2, x3 = parents[:, 0], parents[:, 1], parents[:, 2]
            f = 1*x1**2 + 2*x2**2 + 3*x3**2
            scatter._offsets3d = (x1, x2, f)
            best = data['best']
            best_f = objective(best)
            best_point._offsets3d = ([best[0]], [best[1]], [best_f])
            ax.set_title(f'n=3, Ген {frame}, f={data["fitness"]:.6f}')
            current_frame[0] = frame  
            fig.canvas.draw_idle()  
            return scatter, best_point

        def on_key(event):
            if event.key == 'left':
                if current_frame[0] > 0:
                    current_frame[0] -= 1
                    update(current_frame[0])
            elif event.key == 'right':
                if current_frame[0] < len(es.history)-1:
                    current_frame[0] += 1
                    update(current_frame[0])
            elif event.key == ' ':
                if ani[0]:
                    if paused[0]:
                        ani[0].event_source.start()
                        paused[0] = False
                        print("Анимация продолжена")
                    else:
                        ani[0].event_source.stop()
                        paused[0] = True
                        print("Анимация приостановлена")

        ani[0] = FuncAnimation(fig, update, frames=len(es.history), 
                              interval=300, repeat=True, repeat_delay=2000)
        
        fig.canvas.mpl_connect('key_press_event', on_key)
        ax.legend()
        
        plt.figtext(0.02, 0.02, "Управление: ← → - переключение поколений, Пробел - пауза", 
                   fontsize=10, ha='left')
        
        plt.show()
        return

    # --- n=2 (полный 3D) ---
    X, Y = np.meshgrid(x, x)
    Z = 1*X**2 + 2*Y**2
    coords = [X, Y, Z]

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(coords[0], coords[1], coords[2], cmap='viridis', alpha=0.6, linewidth=0)

    scatter = ax.scatter([], [], [], c='red', s=40, label='Популяция', depthshade=False)
    best_point = ax.scatter([], [], [], c='yellow', s=120, marker='*', label='Лучший', depthshade=False)

    ax.set_xlabel('x₁')
    ax.set_ylabel('x₂')
    ax.set_zlabel('f(x)')
    ax.set_title('Axis Parallel Hyper-Ellipsoid (n=2)\nf(x) = x₁² + 2x₂²')

    def update(frame):
        data = es.history[frame]
        parents = data['parents']
        x1, x2 = parents[:, 0], parents[:, 1]
        f = np.array([objective(p) for p in parents])
        scatter._offsets3d = (x1, x2, f)
        best = data['best']
        best_f = objective(best)
        best_point._offsets3d = ([best[0]], [best[1]], [best_f])
        ax.set_title(f'n=2, Ген {frame}, f={data["fitness"]:.6f}')
        current_frame[0] = frame  
        fig.canvas.draw_idle()  
        return scatter, best_point

    def on_key(event):
        if event.key == 'left':
            if current_frame[0] > 0:
                current_frame[0] -= 1
                update(current_frame[0])
        elif event.key == 'right':
            if current_frame[0] < len(es.history)-1:
                current_frame[0] += 1
                update(current_frame[0])
        elif event.key == ' ':
            if ani[0]:
                if paused[0]:
                    ani[0].event_source.start()
                    paused[0] = False
                    print("Анимация продолжена")
                else:
                    ani[0].event_source.stop()
                    paused[0] = True
                    print("Анимация приостановлена")

    # Создаем анимацию
    ani[0] = FuncAnimation(fig, update, frames=len(es.history), 
                          interval=250, repeat=True, repeat_delay=2000)
    
    fig.canvas.mpl_connect('key_press_event', on_key)
    ax.legend()
    
    # Добавляем подсказку по управлению
    plt.figtext(0.02, 0.02, "Управление: ← → - переключение поколений, Пробел - пауза", 
               fontsize=10, ha='left')
    
    plt.tight_layout()
    plt.show()


# Исследование параметров + графики
def parameter_study():
    print("\n" + "="*70)
    print("ИССЛЕДОВАНИЕ ПАРАМЕТРОВ")
    print("="*70)

    configs = [(10, 50), (20, 100), (50, 200)]
    results = []

    for n in [2, 3]:
        print(f"\n--- n = {n} ---")
        for mu, lam in configs:
            es = EvolutionStrategy(n_dim=n, mu=mu, lambda_=lam, max_stagnation=50)
            t = es.run()
            results.append({
                'n': n, 'mu': mu, 'λ': lam,
                'gens': es.generation, 'time': t, 'f': es.best_fitness
            })

    # Таблица
    print("\n{:<3} {:>4} {:>4} {:>8} {:>8} {:>12}".format('n', 'μ', 'λ', 'Ген', 'Время', 'f(min)'))
    print("-"*55)
    for r in results:
        print("{:<3} {:>4} {:>4} {:>8} {:>8.3f} {:>12.6e}".format(
            r['n'], r['mu'], r['λ'], r['gens'], r['time'], r['f']))

    # Графики
    mus = [10, 20, 50]
    n2_time = [np.mean([r['time'] for r in results if r['n']==2 and r['mu']==m]) for m in mus]
    n3_time = [np.mean([r['time'] for r in results if r['n']==3 and r['mu']==m]) for m in mus]
    n2_gens = [np.mean([r['gens'] for r in results if r['n']==2 and r['mu']==m]) for m in mus]
    n3_gens = [np.mean([r['gens'] for r in results if r['n']==3 and r['mu']==m]) for m in mus]
    n2_f = [np.mean([r['f'] for r in results if r['n']==2 and r['mu']==m]) for m in mus]
    n3_f = [np.mean([r['f'] for r in results if r['n']==3 and r['mu']==m]) for m in mus]

    plt.figure(figsize=(10,6))
    plt.plot(mus, n2_time, 'o-', label='n=2', color='blue')
    plt.plot(mus, n3_time, 's-', label='n=3', color='red')
    plt.xlabel('μ'); plt.ylabel('Время (с)'); plt.title('Время от размера популяции')
    plt.legend(); plt.grid(); plt.show()

    plt.figure(figsize=(10,6))
    plt.plot(mus, n2_gens, 'o-', label='n=2', color='blue')
    plt.plot(mus, n3_gens, 's-', label='n=3', color='red')
    plt.xlabel('μ'); plt.ylabel('Поколения'); plt.title('Поколения от размера популяции')
    plt.legend(); plt.grid(); plt.show()

    plt.figure(figsize=(10,6))
    plt.semilogy(mus, n2_f, 'o-', label='n=2', color='blue')
    plt.semilogy(mus, n3_f, 's-', label='n=3', color='red')
    plt.xlabel('μ'); plt.ylabel('f(min)'); plt.title('Точность от размера популяции')
    plt.legend(); plt.grid(); plt.show()


# Запуск
if __name__ == "__main__":
    print("Вариант 2: Axis parallel hyper-ellipsoid")
    print("f(x) = σ i·x_i², i=1..n, x_i ∈ [-5.12, 5.12]")
    print("Минимум: f(0)=0")
    print("Управление: ← → — переключение поколений, Пробел — пауза/продолжение анимации")

    animate_3d(n_dim=2)
    animate_3d(n_dim=3)
    parameter_study()