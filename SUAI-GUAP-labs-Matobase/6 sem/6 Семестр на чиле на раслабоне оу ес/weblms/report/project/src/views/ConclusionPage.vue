<!-- src/views/ConclusionPage.vue -->
<template>
  <div class="conclusion-page">
    <div class="content-container">
      <h1>Заключение</h1>
      <p style="text-align: center;">Общие выводы и рекомендации по реализации умного города.</p>

      <!-- Основное заключение -->
      <div class="conclusion-text">
        <h2 class="main-heading">Что мы узнали</h2>
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
        <img src="@/assets/smart-city-graph.png" alt="Прогнозы и данные" class="data-image" />
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
      'Проект умного города представляет собой амбициозную задачу по внедрению современных технологий в городской инфраструктуре. Цель состоит в повышении уровня жизни жителей города, улучшении экологии, безопасности и управляемости общественными ресурсами.'
    );

    const keyFindings = ref(
      'Ключевые выводы указывают на важность комплексного подхода при реализации подобных проектов. Необходимо учитывать потребности всех групп населения, обеспечивая равный доступ к технологиям и услугам.'
    );

    const innovationNote = ref(
      'Инновационные технологии постоянно развиваются. Следовательно, успех проекта умного города напрямую зависит от гибкости его архитектуры и способности адаптироваться к новым вызовам и возможностям.'
    );

    const recommendations = ref([
      'Создание единой платформы для управления городскими ресурсами.',
      'Развитие инфраструктуры для использования возобновляемых источников энергии.',
      'Инвестирование в системы интеллектуального управления трафиком.',
      'Международное сотрудничество и обмен опытом.',
      'Обучение населения использованию новых технологий.'
    ]);

    const dataForecast = ref(
      'Согласно прогнозам, к 2030 году более 70% населения мира будет жить в городах. Это создаёт новые вызовы для городской инфраструктуры и повышает спрос на умные решения.'
    );

    const dataBenefits = ref(
      'Умные города могут значительно сократить расходы на энергопотребление, улучшить транспортную доступность и повысить качество жизни.'
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
