import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Установка базовых значений для симуляции при N=25
n_value = 25
t_start = n_value
t_end = n_value + 100
intensity_a = (n_value + 8) / (n_value + 24)
intensity_b = (n_value + 9) / (n_value + 25)
total_intensity = intensity_a + intensity_b

# Общее число повторений эксперимента
repeats = 100  # Для лучшей статистики

# Разделение временного отрезка на равные бинны
bins_num = 25
bin_size = (t_end - t_start) / bins_num
bin_limits = np.linspace(t_start, t_end, bins_num + 1)

# Симуляция событий в Пуассоновском процессе
def create_poisson_times(rate_val, begin_t, finish_t):
    events_list = []
    curr_time = begin_t
    while curr_time < finish_t:
        wait_time = np.random.exponential(1 / rate_val)
        curr_time += wait_time
        if curr_time < finish_t:
            events_list.append(curr_time)
    return np.array(events_list)

# Создание наборов событий для разных потоков
np.random.seed(42)
events_a = [create_poisson_times(intensity_a, t_start, t_end) for _ in range(repeats)]
events_b = [create_poisson_times(intensity_b, t_start, t_end) for _ in range(repeats)]
events_merged = [np.sort(np.concatenate((a_events, b_events))) for a_events, b_events in zip(events_a, events_b)]
events_total_direct = [create_poisson_times(total_intensity, t_start, t_end) for _ in range(repeats)]

# Расчет количества событий в каждом бинне
def bin_event_counts(event_times, limits):
    hist_values, _ = np.histogram(event_times, bins=limits)
    return hist_values

# Сбор матриц счетчиков для всех повторений
matrix_a = np.array([bin_event_counts(ev, bin_limits) for ev in events_a])
matrix_b = np.array([bin_event_counts(ev, bin_limits) for ev in events_b])
matrix_merged = np.array([bin_event_counts(ev, bin_limits) for ev in events_merged])
matrix_direct = np.array([bin_event_counts(ev, bin_limits) for ev in events_total_direct])

# Процедура оценки параметров и теста на Пуассон
def evaluate_and_test(data_matrix, theor_rate, bin_width, alpha_level=0.05):
    flattened = data_matrix.ravel()
    obs_count = len(flattened)
    
    # Вычисление базовых статистик
    avg_count = np.mean(flattened)
    var_count = np.var(flattened)
    
    # Оценка реальной интенсивности
    rate_est = avg_count / bin_width
    
    # Параметры для теоретического распределения
    mu_param = rate_est * bin_width
    max_count_val = int(flattened.max()) + 1
    prob_theor = stats.poisson.pmf(np.arange(max_count_val + 1), mu_param)
    freq_theor = prob_theor * obs_count
    
    # Подсчет фактических частот
    unique_vals, freq_emp = np.unique(flattened, return_counts=True)
    freq_emp_extended = np.zeros(max_count_val + 1)
    for val, fr in zip(unique_vals, freq_emp):
        freq_emp_extended[val] = fr
    
    # Группировка редких исходов для теста
    sufficient = freq_theor >= 5
    if sufficient.sum() < 2:
        sufficient = freq_theor > 0
    freq_emp_grouped = np.where(sufficient, freq_emp_extended[:len(sufficient)], freq_emp_extended[:len(sufficient)].sum())
    freq_theor_grouped = np.where(sufficient, freq_theor[:len(sufficient)], freq_theor[:len(sufficient)].sum())
    
    # Масштабирование теоретических частот под эмпирику
    if freq_theor_grouped.sum() > 0:
        freq_theor_grouped *= (freq_emp_grouped.sum() / freq_theor_grouped.sum())
    
    # Применение критерия согласия
    valid_mask = (freq_theor_grouped > 0) & (freq_emp_grouped > 0)
    if valid_mask.sum() > 1:
        chi_obs, p_obs = stats.chisquare(freq_emp_grouped[valid_mask], freq_theor_grouped[valid_mask])
        dof = valid_mask.sum() - 2
        chi_thresh = stats.chi2.ppf(1 - alpha_level, dof)
    else:
        chi_obs, chi_thresh, p_obs = 0, np.inf, 1.0
        dof = 1
    
    hyp_ok = chi_obs < chi_thresh
    
    return {
        'rate_est': rate_est,
        'rate_theor': theor_rate,
        'chi_obs': chi_obs,
        'chi_thresh': chi_thresh,
        'hyp_ok': hyp_ok,
        'avg': avg_count,
        'var': var_count,
        'uniq': unique_vals,
        'freq_emp': freq_emp,
        'freq_theor': freq_theor[:len(unique_vals)]
    }

# Запуск оценки для каждого типа потока
res_a = evaluate_and_test(matrix_a, intensity_a, bin_size)
res_b = evaluate_and_test(matrix_b, intensity_b, bin_size)
res_merged = evaluate_and_test(matrix_merged, total_intensity, bin_size)
res_direct = evaluate_and_test(matrix_direct, total_intensity, bin_size)

# Отображение основных метрик
for tag, metrics in [("X1", res_a), ("X2", res_b), ("Xpr (merged)", res_merged), ("X (direct)", res_direct)]:
    print(f"\nОценка для {tag}:")
    print(f"Интенсивность (оценка): {metrics['rate_est']:.4f}, (теория): {metrics['rate_theor']:.4f}")
    print(f"Среднее значение: {metrics['avg']:.4f}, Варьяция: {metrics['var']:.4f}")
    print(f"Хи-квадрат наблюдаемое: {metrics['chi_obs']:.2f}, Пороговое: {metrics['chi_thresh']:.2f}, Принято: {metrics['hyp_ok']}")

# Построение диаграмм событий для первых симуляций
fig, ax_grid = plt.subplots(2, 2, figsize=(12, 8), sharex=True)
example_events = [events_a[0], events_b[0], events_merged[0], events_total_direct[0]]
titles_list = ["Поток X1", "Поток X2", "Смешанный поток Xpr", "Непосредственный суммарный X"]
for ax, ev_data, title_str in zip(ax_grid.ravel(), example_events, titles_list):
    ax.eventplot(ev_data, orientation='horizontal', colors='green')
    ax.set_xlim(t_start, t_end)
    ax.set_title(title_str)
    ax.set_xlabel('t (время)')
    ax.set_yticks([])
plt.tight_layout()
plt.show()

# Сравнение эмпирических и теоретических распределений
fig, ax_grid = plt.subplots(2, 2, figsize=(12, 8))
data_matrices = [matrix_a, matrix_b, matrix_merged, matrix_direct]
analyses_list = [res_a, res_b, res_merged, res_direct]
for ax, flat_data, anal_res, title_str in zip(ax_grid.ravel(), data_matrices, analyses_list, titles_list):
    max_val = int(flat_data.max()) + 1
    ax.hist(flat_data.ravel(), bins=range(max_val + 1), density=True, alpha=0.7, color='lightgreen', label='Наблюдается')
    x_axis = np.arange(0, max_val)
    mu_fit = anal_res['rate_est'] * bin_size
    ax.plot(x_axis, stats.poisson.pmf(x_axis, mu_fit), 'b^-', label='Модель Пуассона')
    ax.set_title(f'Гистограмма {title_str}')
    ax.set_xlabel('События в бинне')
    ax.set_ylabel('Вероятностная плотность')
    ax.legend()
plt.tight_layout()
plt.show()