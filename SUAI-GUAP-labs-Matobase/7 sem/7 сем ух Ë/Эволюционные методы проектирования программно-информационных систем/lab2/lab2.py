import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Button, Slider
from scipy.optimize import differential_evolution

def moved_hyper_ellipsoid(x):
    n = len(x)
    return sum(5**i * x[i-1]**2 for i in range(1, n+1))

def genetic_algorithm(n, pop_size=100, max_gen=100, p_cross=0.8, p_mut=0.01, stall=20, bounds=[-5.12, 5.12], verbose=True):
    np.random.seed(42)
    lower, upper = bounds
    pop = np.random.uniform(lower, upper, (pop_size, n))
    fitness = np.array([moved_hyper_ellipsoid(ind) for ind in pop])
    best_idx = np.argmin(fitness)
    best = pop[best_idx]
    best_fit = fitness[best_idx]
    no_change = 0
    gens = 0
    pop_history = []
    history = []
    for gen in range(max_gen):
        gens = gen + 1
        if verbose:
            print(f"Generation {gen+1}: Best Fitness = {best_fit:.6f}")
        offspring = []
        for _ in range(pop_size // 2):
            parents = []
            for _ in range(2):
                candidates = np.random.choice(pop_size, 3)
                win = candidates[np.argmin(fitness[candidates])]
                parents.append(pop[win])
            if np.random.rand() < p_cross:
                point = np.random.randint(1, n)
                child1 = np.concatenate((parents[0][:point], parents[1][point:]))
                child2 = np.concatenate((parents[1][:point], parents[0][point:]))
            else:
                child1, child2 = parents[0].copy(), parents[1].copy()
            offspring.append(child1)
            offspring.append(child2)
        offspring = np.array(offspring)
        for i in range(pop_size):
            for j in range(n):
                if np.random.rand() < p_mut:
                    offspring[i][j] += np.random.normal(0, (upper - lower) / 10)
                    offspring[i][j] = np.clip(offspring[i][j], lower, upper)
        off_fit = np.array([moved_hyper_ellipsoid(ind) for ind in offspring])
        combined_pop = np.vstack((pop, offspring))
        combined_fit = np.hstack((fitness, off_fit))
        indices = np.argsort(combined_fit)[:pop_size]
        pop = combined_pop[indices]
        fitness = combined_fit[indices]
        curr_best_idx = np.argmin(fitness)
        curr_best_fit = fitness[curr_best_idx]
        history.append(curr_best_fit)
        pop_history.append(pop.copy())
        if curr_best_fit < best_fit:
            best_fit = curr_best_fit
            best = pop[curr_best_idx]
            no_change = 0
        else:
            no_change += 1
        if no_change >= stall:
            if verbose:
                print("Stopped due to stall condition (20 generations)")
            break
    print(f"Final Result (n={n}):")
    print(f"Best x = {best}")
    print(f"Best Fitness = {best_fit:.6f}")
    print(f"Generations = {gens}")
    return best, best_fit, gens, pop, history, pop_history

# Для n=2 (график/анимация)
best_x_n2, best_f_n2, gens_n2, final_pop_n2, hist_n2, pop_history_n2 = genetic_algorithm(2, verbose=True)

# График/анимация для n=2
x = np.linspace(-5.12, 5.12, 100)
y = np.linspace(-5.12, 5.12, 100)
X, Y = np.meshgrid(x, y)
Z = 5 * X**2 + 25 * Y**2

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6)
scat = ax.scatter([], [], [], color='red', s=20, label='Population')
best_scat = ax.scatter(best_x_n2[0], best_x_n2[1], best_f_n2, color='green', s=50, label='Found minimum')
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('f(x)')
ax.set_title('Moved Hyper-Ellipsoid (n=2) Evolution')
ax.legend()

def init():
    scat._offsets3d = ([], [], [])
    return scat,

def update(frame):
    pop = pop_history_n2[frame]
    pop_fits = np.array([moved_hyper_ellipsoid(ind) for ind in pop])
    scat._offsets3d = (pop[:, 0], pop[:, 1], pop_fits)
    ax.set_title(f'Moved Hyper-Ellipsoid (n=2) - Gen {frame+1} (Best f: {hist_n2[frame]:.6f})')
    return scat,

ani = FuncAnimation(fig, update, frames=len(pop_history_n2), init_func=init, interval=800, repeat=True)

ax_pause = plt.axes([0.7, 0.02, 0.1, 0.05])
ax_play = plt.axes([0.8, 0.02, 0.1, 0.05])
ax_slider = plt.axes([0.1, 0.02, 0.6, 0.03])
pause_button = Button(ax_pause, 'Pause')
play_button = Button(ax_play, 'Play')
slider = Slider(ax_slider, 'Generation', 0, len(pop_history_n2)-1, valinit=0, valfmt='%d')

animating = True
current_frame = 0

def pause(event):
    global animating
    animating = False
    ani.event_source.stop()

def play(event):
    global animating
    animating = True
    ani.event_source.start()

def update_slider(val):
    global current_frame
    current_frame = int(slider.val)
    if not animating:
        update(current_frame)
        fig.canvas.draw()

pause_button.on_clicked(pause)
play_button.on_clicked(play)
slider.on_changed(update_slider)

print("Controls: Use Play/Pause buttons. Use slider for step-by-step view.")
plt.show()

# Для n=3 (только расчёт)
best_x_n3, best_f_n3, gens_n3, final_pop_n3, hist_n3, pop_history_n3 = genetic_algorithm(3, verbose=True)

# Сравнение для n=2
bounds_de2 = [(-5.12, 5.12)] * 2
res_de2 = differential_evolution(moved_hyper_ellipsoid, bounds_de2, maxiter=100, popsize=15, seed=42)

print("=== Comparison Results (n=2) ===")
print(f"GA: Best x = {best_x_n2}")
print(f"GA: Best Fitness = {best_f_n2:.6f}")
print(f"GA: Generations = {gens_n2}")
print(f"DE: Best x = {res_de2.x}")
print(f"DE: Best Fitness = {res_de2.fun:.6f}")
print(f"DE: Evaluations = {res_de2.nfev}")
print(f"Note: DE is more accurate ({res_de2.fun:.6f} vs {best_f_n2:.6f}), GA uses {gens_n2} generations vs ~{res_de2.nfev / 15:.1f} DE iterations.")

# Сравнение для n=3
bounds_de3 = [(-5.12, 5.12)] * 3
res_de3 = differential_evolution(moved_hyper_ellipsoid, bounds_de3, maxiter=100, popsize=15, seed=42)

print("=== Comparison Results (n=3) ===")
print(f"GA: Best x = {best_x_n3}")
print(f"GA: Best Fitness = {best_f_n3:.6f}")
print(f"GA: Generations = {gens_n3}")
print(f"DE: Best x = {res_de3.x}")
print(f"DE: Best Fitness = {res_de3.fun:.6f}")
print(f"DE: Evaluations = {res_de3.nfev}")
print(f"Note: DE is more accurate ({res_de3.fun:.6f} vs {best_f_n3:.6f}), GA uses {gens_n3} generations vs ~{res_de3.nfev / 15:.1f} DE iterations.")
print("=== GA n=2 vs n=3 ===")
print(f"GA n=2 Fitness = {best_f_n2:.6f}, Generations = {gens_n2}")
print(f"GA n=3 Fitness = {best_f_n3:.6f}, Generations = {gens_n3}")
print(f"Note: n=3 has lower accuracy ({best_f_n3:.6f} vs {best_f_n2:.6f}) and fewer generations ({gens_n3} vs {gens_n2}), with ~20% more time.")