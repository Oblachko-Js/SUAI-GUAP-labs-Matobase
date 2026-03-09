<!-- src/views/HomePage.vue -->
<template>
  <div class="home-page">
    <h1>Характеристики линий связи</h1>
    <p>Разбираем ключевые параметры каналов передачи: полоса, затухание, BER, задержки и помехи.</p>

    <!-- Картинка сверху -->
    <img src="@/assets/comm-fiber-header.jpg" alt="Линии связи" class="header-image" />

    <!-- Прямоугольник с текстом -->
    <div class="text-box">
      <div class="text-content">
        <h2>О чём проект</h2>
        <p>Здесь собраны базовые сведения о характеристиках линий связи: пропускная способность, затухание, уровень шума и помех, задержки распространения и джиттер, а также показатели качества вроде BER (битовых ошибок) и SNR.</p>
        <p>Мы сравниваем проводные (витая пара, коаксиал, оптоволокно) и беспроводные среды (RF, микроволны), рассматриваем их физические ограничения: дисперсию, отражения, многолучевость, кросс‑наводки, нелинейности усилителей.</p>
        <p>Цель — дать краткие практические рекомендации по выбору среды и параметров канала под тип задач: датчики IoT, широкополосная передача, магистраль, мобильные сети, реального времени и т. п.</p>
      </div>
    </div>

    <!-- Кнопка узнать больше -->
    <button @click="goToTechnology" class="cta-button">К параметрам и видам линий</button>
  </div>
</template>

<script>
export default {
  name: "HomePage",
  
  // Методы компонента
  methods: {
    goToTechnology() {
      // Прокручиваем страницу вверх
      window.scrollTo({ top: 0, behavior: 'smooth' });

      // Переходим на страницу /technology
      this.$router.push("/technology");
    },
  },

  // Хуки жизненного цикла Vue.js
  mounted() {
    console.log("HomePage компонента смонтирован");
  },

  beforeUnmount() {
    // Очистка ресурсов, если нужно
    console.log("HomePage компонента уничтожен");
  }
};
</script>

<style scoped>
/* Сброс отступов для всех элементов */
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

/* Обеспечиваем полное использование доступной области */
html, body {
  margin: 0;
  padding: 0;
  width: 100%;
  height: 100%;
  overflow-x: hidden; /* Убираем горизонтальную прокрутку */
}

/* Контейнер для страницы */
.home-page {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start; /* Элементы выравниваются по верхнему краю */
  width: 100%; /* Занимает всю ширину */
  min-height: 100vh; /* Занимает всю высоту экрана */
  font-family: 'Arial', sans-serif;
  animation: fadeIn 1.5s ease-out;
  overflow: hidden; /* Убираем прокрутку */
  text-align: center;
  padding-top: 50px; /* Отступ сверху */
}

/* Анимация */
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

/* Стили для текста */
h1 {
  font-size: 2.5rem;
  font-weight: bold;
  margin-bottom: 20px;
}

p {
  font-size: 1.2rem;
  margin-bottom: 30px;
}

/* Стили для кнопки */
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
}

.cta-button:hover {
  background-color: #e6e6e6;
  transform: translateY(-5px);
}

/* Стили для картинки сверху */
.header-image {
  width: 80%; /* Картинка будет шириной 80% от родительского элемента */
  height: auto; /* Пропорциональная высота */
  max-width: 1000px; /* Ограничиваем максимальную ширину */
  object-fit: cover;
  border-radius: 10px;
  margin-bottom: 30px; /* Отступ снизу */
}

/* Стили для блока с текстом */
.text-box {
  background-color: #333; /* Фон прямоугольника */
  color: white; /* Цвет текста */
  padding: 20px;
  border-radius: 10px;
  width: 80%; /* Ширина блока */
  max-width: 1000px;
  margin-top: 30px;
  margin-bottom: 50px; /* Отступ снизу для расположения кнопки ниже */
}

.text-box .text-content {
  width: 100%; /* Занимает всю доступную ширину */
}

.text-box h2 {
  font-size: 2rem;
  margin-bottom: 15px;
  text-align: center; /* Заголовок по центру */
}

.text-box p {
  font-size: 1.2rem;
  margin-bottom: 15px;
  text-align: justify; /* Текст по ширине */
}

/* Адаптивные стили */
@media (max-width: 1200px) {
  .home-page {
    margin-top: 190px;
    padding: 15px;
  }
}

@media (max-width: 800px) {
  .header-image {
    width: 100%; /* Картинка будет занимать всю ширину */
    max-width: none; /* Убираем ограничение по ширине */
  }
  .text-box {
    width: 90%; /* Уменьшаем ширину блока с текстом */
  }
  .home-page {
    margin-top: 190px;
    padding: 15px;
  }
}

@media (max-width: 550px) {
  .text-box p {
    font-size: 1rem;
  }
  .home-page {
    margin-top: 190px;
    padding: 15px;
  }
}
</style>
