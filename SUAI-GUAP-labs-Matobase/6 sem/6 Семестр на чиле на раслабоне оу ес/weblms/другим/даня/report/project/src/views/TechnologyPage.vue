<!-- src/views/TechnologyPage.vue -->
<template>
  <div class="technology-page fade-in">
    <h1 class="fade-in">Параметры и виды линий связи</h1>
    <p class="centered-text fade-in">Ключевые характеристики канала и сравнение медных, оптических и беспроводных сред.</p>

    <!-- Раздел с технологиями -->
    <div class="tech-section fade-in">
      <h2>Полоса пропускания</h2>
      <p>Полоса пропускания определяет диапазон частот, который канал способен передавать без существенных искажений. Широкая полоса допускает более высокие скорости передачи. Для медных линий полоса ограничена скин‑эффектом и емкостно‑индуктивными потерями; для оптики — спектром источника и дисперсией; для радио — выделенным частотным ресурсом и фильтрацией.</p>
      <figure class="tech-figure">
        <img src="@/assets/channel-frequency-response.png" alt="АЧХ канала (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Идея АЧХ: чем шире полезная полоса, тем выше потенциальная скорость.</figcaption>
      </figure>
    </div>

    <div class="tech-section fade-in">
      <h2>Затухание и шум</h2>
      <p>Затухание — снижение амплитуды сигнала вдоль линии. Для витой пары возрастает с частотой и длиной; для коаксиала — ниже, но заметно на высоких частотах; для оптики — измеряется в дБ/км (обычно 0.2–0.35 дБ/км для одномода). Шум (тепловой, импульсный) определяет нижнюю границу SNR и вместе с полосой задаёт допустимую скорость при заданной BER.</p>
      <figure class="tech-figure">
        <img src="@/assets/attenuation-vs-frequency.png" alt="График затухания (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Затухание и уровень шума задают предел дальности/скорости.</figcaption>
      </figure>
    </div>

    <div class="tech-section fade-in">
      <h2>Ошибки (BER) и модуляция</h2>
      <p>BER — доля ошибочных битов. На BER влияют SNR, тип модуляции (QPSK, 16/64‑QAM), корректирующее кодирование (FEC) и частотные искажения канала. Более «плотные» созвездия требуют более высокого SNR для той же BER.</p>
      <figure class="tech-figure">
        <img src="@/assets/qam-constellation.png" alt="Диаграмма созвездия (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Созвездия QAM: рост порядка повышает требования к SNR.</figcaption>
      </figure>
    </div>

    <div class="tech-section fade-in">
      <h2>Задержка и джиттер</h2>
      <p>Задержка складывается из распространения (зависит от среды и длины), обработки и очередей. Джиттер — вариация задержки во времени. Для приложений реального времени (VoIP, индустриальный контроль) важны низкие задержки и стабильность.</p>
      <figure class="tech-figure">
        <img src="@/assets/network-latency-jitter.png" alt="Схема задержек (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Задержка распространения + обработка + очередь дают итоговую задержку.</figcaption>
      </figure>
    </div>

    <div class="tech-section fade-in">
      <h2>Среды передачи</h2>
      <p><strong>Витая пара</strong> — дешево, до 1–10 Гбит/с на сотни метров (Cat5e/6/6A), чувствительна к кросс‑наводкам и помехам. <strong>Коаксиал</strong> — лучшее экранирование и дальность для RF. <strong>Оптоволокно</strong> — огромная полоса, низкое затухание, километры без повторителей. <strong>Беспроводная связь</strong> — гибкость и мобильность, но подвержена многолучевости и ограничению спектра.</p>
      <figure class="tech-figure">
        <img src="@/assets/media-comparison.png" alt="Среды передачи (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Сравнение: медь vs оптика vs радио — выбор по требованиям.</figcaption>
      </figure>
    </div>

    <div class="tech-section fade-in">
      <h2>Практические рекомендации</h2>
      <p>IoT и телеметрия — узкая полоса, высокая помехоустойчивость (FSK, LoRa, DSSS). Камеры и VR — широкая полоса (оптика, Wi‑Fi 6/7). Магистрали — оптика (DWDM). Реальное время — низкий джиттер, приоритет QoS.</p>
      <figure class="tech-figure">
        <img src="@/assets/application-mapping.png" alt="Рекомендации (пример иллюстрации)" class="tech-image fade-in" />
        <figcaption>Выбор параметров зависит от требований приложений.</figcaption>
      </figure>
    </div>

    <!-- Кнопка для перехода на IssuesPage -->
    <button @click="goToIssues" class="cta-button">Перейти к искажениям и проблемам</button>
  </div>
</template>

<script>
export default {
  name: 'TechnologyPage',
  methods: {
    goToIssues() {
      // Прокрутить страницу вверх
      window.scrollTo({
        top: 0,
        behavior: 'smooth',
      });

      // Переход на страницу IssuesPage
      this.$router.push("/issues");
    },
  },
};
</script>

<style scoped>
/* Анимация плавного появления */
@keyframes fadeIn {
  from {
    opacity: 0;
    transform: translateY(20px);
  }
  to {
    opacity: 1;
    transform: translateY(0);
  }
}

/* Применение анимации ко всем элементам */
.fade-in {
  animation: fadeIn 1.5s ease-out;
}

/* Стиль для страницы */
.technology-page {
  margin-top: 250px;
  text-align: center;
  padding: 20px;
  max-width: 1200px;
  margin: 0 auto;
  min-height: 100vh;
  overflow: auto;
  font-family: 'Arial', sans-serif;
  line-height: 1.6;
}

h1 {
  font-size: 2rem;
  color: #333;
  margin-bottom: 20px;
}

p {
  font-size: 1.1rem;
  color: #555;
  text-align: justify;
  margin-bottom: 15px;
}

strong {
  font-weight: bold;
  color: #2d3d55;
}

.tech-section {
  margin-top: 30px;
}

.tech-section h2 {
  font-size: 2rem;
  margin-bottom: 10px;
}

.tech-figure {
  margin-bottom: 20px;
}

.tech-image {
  width: 600px;  /* Увеличенная ширина */
  height: 350px;  /* Увеличенная высота */
  object-fit: cover;
  border-radius: 10px;
  margin-bottom: 10px;
}

figcaption {
  font-size: 1rem;
  color: #666;
  margin-top: 10px;
}

.centered-text {
  text-align: center;
}

.cta-button {
  padding: 12px 24px;
  font-size: 1.1rem;
  font-weight: bold;
  color: #1e3c72;
  background-color: #ffffff;
  border: none;
  border-radius: 8px;
  cursor: pointer;
  transition: background-color 0.3s ease, transform 0.3s ease;
  margin-top: 20px; /* Отступ сверху для кнопки */
}

.cta-button:hover {
  background-color: #e6e6e6;
  transform: translateY(-5px);
}

@media (max-width: 1200px) {
  .technology-page {
    margin-top: 170px;
    padding: 15px;
  }
}

@media (max-width: 800px) {
  .technology-page {
    margin-top: 170px;
    padding: 10px;
  }
}

@media (max-width: 550px) {
  .technology-page {
    margin-top: 180px;
    padding: 5px;
  }
  h1 {
    font-size: 1.5rem;
  }
  p {
    font-size: 1rem;
  }
}
</style>
