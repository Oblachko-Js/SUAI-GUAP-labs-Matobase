import numpy as np
import matplotlib.pyplot as plt

# Данные на основе моих + экспериментов
pop_sizes = [50, 100, 200]
best_f_pop = [0.045, 0.022, 0.008]
gens_pop = [35, 55, 70]
time_pop = [0.15, 0.30, 0.60]

p_cross_vals = [0.6, 0.8, 0.9]
best_f_cross = [0.035, 0.022, 0.028]
gens_cross = [45, 55, 65]
time_cross = [0.25, 0.30, 0.35]

p_mut_vals = [0.005, 0.01, 0.05]
best_f_mut = [0.048, 0.022, 0.012]
gens_mut = [40, 55, 75]
time_mut = [0.20, 0.30, 0.45]

fig, axs = plt.subplots(1, 3, figsize=(15, 5))

# 1. pop_size
axs[0].plot(pop_sizes, best_f_pop, 'o-', label='Best f')
axs[0].plot(pop_sizes, gens_pop, 's-', label='Generations')
axs[0].plot(pop_sizes, time_pop, '^-', label='Time (s)')
axs[0].set_xlabel('Population Size')
axs[0].set_title('Зависимость от размера популяции')
axs[0].legend(); axs[0].grid(True)

# 2. p_cross
axs[1].plot(p_cross_vals, best_f_cross, 'o-', label='Best f')
axs[1].plot(p_cross_vals, gens_cross, 's-', label='Generations')
axs[1].plot(p_cross_vals, time_cross, '^-', label='Time (s)')
axs[1].set_xlabel('Crossover Probability')
axs[1].set_title('Зависимость от вероятности кроссовера')
axs[1].legend(); axs[1].grid(True)

# 3. p_mut
axs[2].plot(p_mut_vals, best_f_mut, 'o-', label='Best f')
axs[2].plot(p_mut_vals, gens_mut, 's-', label='Generations')
axs[2].plot(p_mut_vals, time_mut, '^-', label='Time (s)')
axs[2].set_xlabel('Mutation Probability')
axs[2].set_title('Зависимость от вероятности мутации')
axs[2].legend(); axs[2].grid(True)

plt.tight_layout()
plt.show()