import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt

# Параметры моделирования для N=7
N = 7
T_start = N
T_end = N + 100
lambda1 = (N + 8) / (N + 24)
lambda2 = (N + 9) / (N + 25)
lambda_sum = lambda1 + lambda2

# Количество реализаций для статистического анализа
num_realizations = 100

# Подготовка временных интервалов для анализа
num_bins = 25
bin_length = (T_end - T_start) / num_bins
bin_edges = np.linspace(T_start, T_end, num_bins + 1)

# Функция генерации пуассоновского потока
def generate_poisson_process(rate, start_time, end_time):
    event_times = []
    current_time = start_time
    while current_time < end_time:
        interval = np.random.exponential(1 / rate)
        current_time += interval
        if current_time < end_time:
            event_times.append(current_time)
    return np.array(event_times)

# Генерация реализаций потоков
np.random.seed(42)
process1_events = [generate_poisson_process(lambda1, T_start, T_end) for _ in range(num_realizations)]
process2_events = [generate_poisson_process(lambda2, T_start, T_end) for _ in range(num_realizations)]
combined_events = [np.sort(np.concatenate((events1, events2))) for events1, events2 in zip(process1_events, process2_events)]
direct_sum_events = [generate_poisson_process(lambda_sum, T_start, T_end) for _ in range(num_realizations)]

# Функция подсчета событий в интервалах
def count_events_in_bins(event_times, boundaries):
    counts, _ = np.histogram(event_times, bins=boundaries)
    return counts

# Формирование матриц счетчиков событий
counts_process1 = np.array([count_events_in_bins(events, bin_edges) for events in process1_events])
counts_process2 = np.array([count_events_in_bins(events, bin_edges) for events in process2_events])
counts_combined = np.array([count_events_in_bins(events, bin_edges) for events in combined_events])
counts_direct = np.array([count_events_in_bins(events, bin_edges) for events in direct_sum_events])

# Функция статистического анализа пуассоновского потока
def analyze_poisson_process(count_matrix, theoretical_rate, bin_duration, significance=0.05):
    flat_counts = count_matrix.flatten()
    total_observations = len(flat_counts)
    
    # Вычисление статистических характеристик
    mean_count = np.mean(flat_counts)
    variance_count = np.var(flat_counts)
    
    # Оценка интенсивности потока
    estimated_rate = mean_count / bin_duration
    
    # Подготовка данных для критерия хи-квадрат
    poisson_mean = estimated_rate * bin_duration
    max_count_value = int(flat_counts.max()) + 1
    theoretical_probs = stats.poisson.pmf(np.arange(max_count_value + 1), poisson_mean)
    theoretical_frequencies = theoretical_probs * total_observations
    
    # Эмпирические частоты
    unique_values, empirical_frequencies = np.unique(flat_counts, return_counts=True)
    extended_empirical = np.zeros(max_count_value + 1)
    for val, freq in zip(unique_values, empirical_frequencies):
        extended_empirical[val] = freq
    
    # Группировка ячеек для выполнения условий критерия
    valid_cells = theoretical_frequencies >= 5
    if valid_cells.sum() < 2:
        valid_cells = theoretical_frequencies > 0
    
    grouped_empirical = np.where(valid_cells, extended_empirical[:len(valid_cells)], 
                                extended_empirical[:len(valid_cells)].sum())
    grouped_theoretical = np.where(valid_cells, theoretical_frequencies[:len(valid_cells)], 
                                  theoretical_frequencies[:len(valid_cells)].sum())
    
    # Нормализация теоретических частот
    if grouped_theoretical.sum() > 0:
        grouped_theoretical *= (grouped_empirical.sum() / grouped_theoretical.sum())
    
    # Вычисление статистики хи-квадрат
    valid_mask = (grouped_theoretical > 0) & (grouped_empirical > 0)
    if valid_mask.sum() > 1:
        chi2_stat, p_value = stats.chisquare(grouped_empirical[valid_mask], grouped_theoretical[valid_mask])
        degrees_of_freedom = valid_mask.sum() - 2
        critical_value = stats.chi2.ppf(1 - significance, degrees_of_freedom)
    else:
        chi2_stat, critical_value, p_value = 0, np.inf, 1.0
        degrees_of_freedom = 1
    
    hypothesis_accepted = chi2_stat < critical_value
    
    return {
        'estimated_rate': estimated_rate,
        'theoretical_rate': theoretical_rate,
        'chi2_statistic': chi2_stat,
        'critical_value': critical_value,
        'hypothesis_accepted': hypothesis_accepted,
        'mean': mean_count,
        'variance': variance_count,
        'unique_values': unique_values,
        'empirical_freq': empirical_frequencies,
        'theoretical_freq': theoretical_frequencies[:len(unique_values)]
    }

# Проведение анализа для всех типов потоков
analysis_process1 = analyze_poisson_process(counts_process1, lambda1, bin_length)
analysis_process2 = analyze_poisson_process(counts_process2, lambda2, bin_length)
analysis_combined = analyze_poisson_process(counts_combined, lambda_sum, bin_length)
analysis_direct = analyze_poisson_process(counts_direct, lambda_sum, bin_length)

# Вывод результатов анализа
for label, results in [("Поток 1", analysis_process1), ("Поток 2", analysis_process2), 
                      ("Объединенный поток", analysis_combined), ("Прямой суммарный поток", analysis_direct)]:
    print(f"\nРезультаты для {label}:")
    print(f"Интенсивность: оценка {results['estimated_rate']:.4f}, теоретическая {results['theoretical_rate']:.4f}")
    print(f"Среднее: {results['mean']:.4f}, Дисперсия: {results['variance']:.4f}")
    print(f"Хи-квадрат: {results['chi2_statistic']:.2f}, Критическое значение: {results['critical_value']:.2f}")
    print(f"Гипотеза о пуассоновском распределении: {'принята' if results['hypothesis_accepted'] else 'отвергнута'}")

# Визуализация временных разверток потоков
figure, axes = plt.subplots(2, 2, figsize=(12, 8), sharex=True)
example_events = [process1_events[0], process2_events[0], combined_events[0], direct_sum_events[0]]
plot_titles = ["Поток 1", "Поток 2", "Объединенный поток", "Суммарный поток"]
for axis, events, title in zip(axes.ravel(), example_events, plot_titles):
    axis.eventplot(events, orientation='horizontal', colors='blue')
    axis.set_xlim(T_start, T_end)
    axis.set_title(title)
    axis.set_xlabel('Время')
    axis.set_yticks([])
plt.tight_layout()
plt.show()

# Сравнение эмпирических и теоретических распределений
figure, axes = plt.subplots(2, 2, figsize=(12, 8))
count_matrices = [counts_process1, counts_process2, counts_combined, counts_direct]
analyses = [analysis_process1, analysis_process2, analysis_combined, analysis_direct]
for axis, data, analysis, title in zip(axes.ravel(), count_matrices, analyses, plot_titles):
    max_value = int(data.max()) + 1
    axis.hist(data.ravel(), bins=range(max_value + 1), density=True, alpha=0.7, 
              color='lightblue', label='Эмпирическое')
    x_values = np.arange(0, max_value)
    fitted_mean = analysis['estimated_rate'] * bin_length
    axis.plot(x_values, stats.poisson.pmf(x_values, fitted_mean), 'ro-', 
              label='Пуассоновское')
    axis.set_title(f'Распределение для {title}')
    axis.set_xlabel('Количество событий в интервале')
    axis.set_ylabel('Плотность вероятности')
    axis.legend()
plt.tight_layout()
plt.show()