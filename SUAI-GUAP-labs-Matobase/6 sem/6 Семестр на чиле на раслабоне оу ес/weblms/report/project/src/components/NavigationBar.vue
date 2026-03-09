<!-- src/components/NavigationBar.vue -->
<template>
  <div class="navbar">
    <ul>
      <li><router-link to="/" @click="scrollToTop">Главная</router-link></li>
      <li><router-link to="/technology" @click="scrollToTop">Технические возможности</router-link></li>
      <li><router-link to="/issues" @click="scrollToTop">Проблемы реализации</router-link></li>
      <li><router-link to="/conclusion" @click="scrollToTop">Заключение</router-link></li>
    </ul>
  </div>
</template>

<script>
export default {
  name: 'NavigationBar',
  methods: {
    scrollToTop() {
      // Прокручиваем страницу вверх
      window.scrollTo({ top: 0, behavior: 'smooth' });
    },
  },
};
</script>

<style scoped>
/* Стили для навигационного меню */
.navbar {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  background-color: #333;
  color: white;
  padding: 10px;
  z-index: 1000; /* чтобы меню было поверх других элементов */
}

/* Стили для списка меню */
.navbar ul {
  list-style: none;
  padding: 0;
  display: flex;
  justify-content: center;
  margin: 0;
}

/* Стили для каждого пункта меню */
.navbar li {
  margin: 0 20px;
}

/* Стили для ссылок */
.navbar a {
  color: white;
  text-decoration: none;
  font-size: 18px;
  transition: color 0.3s ease;
}

/* Изменение цвета при наведении на ссылку */
.navbar a:hover {
  color: #ff6347; /* Цвет при наведении */
  text-decoration: underline;
}

/* Адаптивность для экранов менее 1200px */
@media (max-width: 1200px) {
  .navbar {
    flex-direction: column;
    align-items: center;
  }

  .navbar ul {
    flex-direction: column;
  }

  .navbar li {
    margin: 10px 0;
  }
}

/* Адаптивность для экранов менее 800px */
@media (max-width: 800px) {
  .navbar {
    padding: 15px;
  }

  .navbar a {
    font-size: 16px;
  }
}

/* Адаптивность для экранов менее 550px */
@media (max-width: 550px) {
  .navbar a {
    font-size: 14px;
  }
}
</style>
