<!-- src/views/ConclusionPage.vue -->
<template>
  <div class="conclusion-page">
    <div class="content-container">
      <h1>Заключение</h1>
      <p style="text-align: center;">Итоги по характеристикам линий связи и практические рекомендации.</p>

      <!-- Основное заключение -->
      <div class="conclusion-text">
        <h2 class="main-heading">Ключевые выводы</h2>
        <p>{{ mainConclusion }}</p>
        <p>{{ keyFindings }}</p>
        <p>{{ innovationNote }}</p>
      </div>

      <!-- Рекомендации -->
      <div class="recommendations">
        <h2 class="main-heading">Рекомендации</h2>
        <ul>
          <li v-for="(recommendation, index) in recommendations" :key="index">{{ recommendation }}</li>
        </ul>
      </div>

      <!-- Визуализация данных -->
      <div class="data-visualization">
        <h2 class="main-heading">Прогнозы и данные</h2>
        <p>{{ dataForecast }}</p>
        <p>{{ dataBenefits }}</p>
        <img src="@/assets/ber-snr-comparison.png" alt="Сравнение BER/SNR и сред передачи" class="data-image" />
      </div>

      <!-- Кнопки навигации -->
      <div class="buttons">
        <button @click="goToPage('/')">Вернуться на главную</button>
        <button @click="goToPage('/technology')">Подробнее о технических возможностях</button>
      </div>
    </div>
  </div>
</template>

<script>
import { ref } from 'vue';
import { useRouter } from 'vue-router';

export default {
  name: 'ConclusionPage',
  setup() {
    const router = useRouter();

    // Текстовые данные
    const mainConclusion = ref(
      'Качество линии связи определяется совокупностью параметров: полоса пропускания, затухание, SNR, BER, задержка и джиттер. Компромисс между скоростью, дальностью и надежностью задается физикой среды и доступными методами обработки сигнала.'
    );

    const keyFindings = ref(
      'Оптика обеспечивает максимальную полосу и дальность при минимальном затухании; медные линии — дешевле и проще в монтаже на коротких дистанциях; радиоканал — гибкость и мобильность ценой помехоустойчивости и ограниченного спектра.'
    );

    const innovationNote = ref(
      'Практики повышения качества: корректирующее кодирование (FEC), адаптивная модуляция и спектральное разнообразие (MIMO/OFDM), эквалайзеры и фильтрация, компенсация дисперсии, качественное согласование и экранирование.'
    );

    const recommendations = ref([
      'Для магистралей и высоких скоростей — оптоволокно (SMF, DWDM).',
      'Для офиса/коротких линий — витая пара Cat6/6A с контролем NEXT/FEXT.',
      'Для беспроводного доступа — планирование частот и MIMO/OFDM.',
      'Для IoT/дальнобойной телеметрии — узкополосные/робастные схемы (FSK, LoRa), FEC.',
      'Учитывать задержку и джиттер для приложений реального времени (QoS).'
    ]);

    const dataForecast = ref(
      'Увеличение требуемых скоростей и плотности трафика делает критичными грамотный выбор среды, спектра и методов повышения спектральной эффективности.'
    );

    const dataBenefits = ref(
      'Систематический подход к параметрам канала снижает BER и задержки, повышает пропускную способность и надежность сервиса.'
    );

    // Метод навигации
    const goToPage = (page) => {
      window.scrollTo({ top: 0, behavior: 'smooth' }); // Прокрутка наверх
      router.push(page); // Переход по маршруту Vue
    };

    return {
      mainConclusion,
      keyFindings,
      innovationNote,
      recommendations,
      dataForecast,
      dataBenefits,
      goToPage
    };
  }
};
</script>

<style scoped>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

html, body {
  margin: 0;
  padding: 0;
  width: 100%;
  height: 100%;
  overflow-x: hidden;
}

.conclusion-page {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start;
  width: 100%;
  min-height: 100vh;
  font-family: 'Arial', sans-serif;
  animation: fadeIn 1.5s ease-out;
  overflow: hidden;
  text-align: center;
  padding-top: 50px;
}

.content-container {
  max-width: 1200px;
  width: 100%;
  padding: 0 20px;
  margin: 0 auto;
}

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

h1 {
  font-size: 2.5rem;
  font-weight: bold;
  margin-bottom: 20px;
  color: #333;
}

h2.main-heading {
  font-size: 2rem;
  margin-top: 30px;
  margin-bottom: 10px;
  font-weight: 500;
  color: #333;
  text-align: center;
}

p {
  font-size: 1.2rem;
  margin-bottom: 30px;
  color: #4a4a4a;
  line-height: 1.6;
  text-align: justify;
}

ul {
  text-align: left;
  list-style-type: disc;
  padding-left: 20px;
  font-size: 1.1rem;
  margin-bottom: 30px;
  color: #4a4a4a;
}

li {
  margin-bottom: 10px;
}

button {
  padding: 12px 24px;
  font-size: 1.1rem;
  font-weight: bold;
  color: #1e3c72;
  background-color: #ffffff;
  border: none;
  border-radius: 8px;
  cursor: pointer;
  transition: background-color 0.3s ease, transform 0.3s ease;
  margin: 10px;
  display: inline-block;
}

button:hover {
  background-color: #e6e6e6;
  transform: translateY(-5px);
}

.data-visualization .data-image {
  max-width: 100%;
  margin-top: 20px;
  border-radius: 8px;
}

@media (max-width: 1200px) {
  .conclusion-page {
    padding: 15px;
    margin-top: 180px;
  }
}

@media (max-width: 800px) {
  .conclusion-page {
    padding: 10px;
    margin-top: 180px;
  }
}

@media (max-width: 550px) {
  .conclusion-page {
    padding: 5px;
    margin-top: 180px;
  }
  h1 {
    font-size: 1.5rem;
  }
  p {
    font-size: 1rem;
  }
}
</style>
