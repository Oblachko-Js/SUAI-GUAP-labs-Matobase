import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Исходные параметры для N=19
N = 19
T1 = N
T2 = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
lambda_sum = lambda1 + lambda2

# Количество реализаций
K = 100  # Увеличено для большей точности

# Разбиение интервала на 25 равных частей
num_intervals = 25
delta_t = (T2 - T1) / num_intervals
interval_edges = np.linspace(T1, T2, num_intervals + 1)

# Функция для генерации пуассоновского потока с накоплением интервалов
def generate_poisson_stream(lam, t_start, t_end):
    times = [t_start]
    t = t_start
    while True:
        u = np.random.exponential(1 / lam)
        t += u
        if t >= t_end:
            break
        times.append(t)
    return np.array(times)

# Генерация реализаций для потоков X1, X2, X_pr (сумма X1+X2), X (прямой суммарный)
np.random.seed(42)
streams_X1 = [generate_poisson_stream(lambda1, T1, T2) for _ in range(K)]
streams_X2 = [generate_poisson_stream(lambda2, T1, T2) for _ in range(K)]
streams_Xpr = [np.sort(np.concatenate((s1, s2))) for s1, s2 in zip(streams_X1, streams_X2)]
streams_X = [generate_poisson_stream(lambda_sum, T1, T2) for _ in range(K)]

# Функция для подсчета событий в интервалах
def count_events_in_intervals(times, edges):
    if len(times) == 0:
        return np.zeros(len(edges) - 1, dtype=int)
    return np.histogram(times, bins=edges)[0]

# Сбор данных {Xj(i)} для каждого потока
counts_X1 = np.array([count_events_in_intervals(s, interval_edges) for s in streams_X1])
counts_X2 = np.array([count_events_in_intervals(s, interval_edges) for s in streams_X2])
counts_Xpr = np.array([count_events_in_intervals(s, interval_edges) for s in streams_Xpr])
counts_X = np.array([count_events_in_intervals(s, interval_edges) for s in streams_X])

# Функция для статистической обработки
def process_counts(counts, lam_theor, delta_t, alpha=0.05):
    flat_counts = counts.flatten()
    N_sample = len(flat_counts)
    
    # Мат. ожидание и дисперсия
    M_eta = np.mean(flat_counts)
    D_eta = np.var(flat_counts)
    
    # Выборочная интенсивность
    hat_lam = M_eta / delta_t
    
    # Теоретические вероятности и частоты
    mu = hat_lam * delta_t
    max_eta = int(np.max(flat_counts)) + 1
    p_l = stats.poisson.pmf(np.arange(max_eta + 1), mu)
    n_l_teor = p_l * N_sample
    
    # Наблюдаемые частоты
    unique, n_l = np.unique(flat_counts, return_counts=True)
    observed = np.array([np.sum(n_l[unique == k]) if k in unique else 0 for k in range(max_eta + 1)])
    
    # Объединение хвостов (если n_l_teor < 5)
    mask = n_l_teor >= 5
    if np.sum(mask) < 2:
        mask = n_l_teor > 0
    observed = np.where(mask, observed[:len(mask)], observed[:len(mask)].sum())
    expected = np.where(mask, n_l_teor[:len(mask)], n_l_teor[:len(mask)].sum())
    
    # Коррекция сумм
    sum_obs = np.sum(observed)
    sum_exp = np.sum(expected)
    if sum_exp > 0:
        scale_factor = sum_obs / sum_exp
        expected = expected * scale_factor
    
    # Критерий хи-квадрат
    mask = (expected > 0) & (observed > 0)
    if np.sum(mask) > 1:
        chi2_prakt, p_value = stats.chisquare(observed[mask], expected[mask])
        df = np.sum(mask) - 2
        chi2_krit = stats.chi2.ppf(1 - alpha, df)
    else:
        chi2_prakt, chi2_krit, p_value = 0, float('inf'), 1.0
        df = 1
    
    hypothesis_accepted = chi2_prakt < chi2_krit
    
    return {
        'hat_lam': hat_lam,
        'lam_theor': lam_theor,
        'chi2_prakt': chi2_prakt,
        'chi2_krit': chi2_krit,
        'hypothesis_accepted': hypothesis_accepted,
        'M_eta': M_eta,
        'D_eta': D_eta,
        'unique_eta': unique,
        'n_l': n_l,
        'n_l_teor': n_l_teor[:len(unique)]
    }

# Обработка для каждого потока
results_X1 = process_counts(counts_X1, lambda1, delta_t)
results_X2 = process_counts(counts_X2, lambda2, delta_t)
results_Xpr = process_counts(counts_Xpr, lambda_sum, delta_t)
results_X = process_counts(counts_X, lambda_sum, delta_t)

# Вывод результатов
for name, res in [("X1", results_X1), ("X2", results_X2), ("Xpr (сумма)", results_Xpr), ("X (прямой)", results_X)]:
    print(f"\nРезультаты для {name}:")
    print(f"Выборочная интенсивность: {res['hat_lam']:.4f}, Теоретическая: {res['lam_theor']:.4f}")
    print(f"Мат. ожидание: {res['M_eta']:.4f}, Дисперсия: {res['D_eta']:.4f}")
    print(f"chi2_prakt: {res['chi2_prakt']:.2f}, chi2_krit: {res['chi2_krit']:.2f}, Гипотеза принята: {res['hypothesis_accepted']}")

# Графическая интерпретация для всех потоков
fig, axes = plt.subplots(2, 2, figsize=(12, 8), sharex=True)
streams = [streams_X1[0], streams_X2[0], streams_Xpr[0], streams_X[0]]
titles = ["Поток X1", "Поток X2", "Суммарный поток Xpr", "Прямой поток X"]
for ax, stream, title in zip(axes.flatten(), streams, titles):
    ax.eventplot(stream, orientation='horizontal', color='black')
    ax.set_xlim(T1, T2)
    ax.set_title(title)
    ax.set_xlabel('Время t')
    ax.set_yticks([])
plt.tight_layout()
plt.show()

# Гистограммы для всех потоков
fig, axes = plt.subplots(2, 2, figsize=(12, 8))
counts = [counts_X1, counts_X2, counts_Xpr, counts_X]
for ax, count, res, title in zip(axes.flatten(), counts, [results_X1, results_X2, results_Xpr, results_X], titles):
    ax.hist(count.flatten(), bins=range(int(np.max(count)) + 2), density=True, alpha=0.6, label='Эмпирическая')
    mu = res['hat_lam'] * delta_t
    x = np.arange(0, int(np.max(count)) + 1)
    ax.plot(x, stats.poisson.pmf(x, mu), 'ro-', label='Теоретическая Пуассона')
    ax.set_title(f'Гистограмма для {title}')
    ax.set_xlabel('Число событий η')
    ax.set_ylabel('Плотность')
    ax.legend()
plt.tight_layout()
plt.show()