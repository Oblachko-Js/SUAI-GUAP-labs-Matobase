<!-- src/components/SiteFooter.vue -->
<template>
  <div class="footer">
    <div class="footer-content">
      <p>&copy; 2025 Проект "Умный город". Все права защищены.</p>
      <div class="social-links">
        <a href="https://www.facebook.com" target="_blank" rel="noopener noreferrer">Facebook</a>
        <a href="https://www.twitter.com" target="_blank" rel="noopener noreferrer">Twitter</a>
        <a href="https://www.linkedin.com" target="_blank" rel="noopener noreferrer">LinkedIn</a>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'SiteFooter'
};
</script>

<style scoped>
/* Основной контейнер для страницы */
html, body {
  height: 100%; /* Занимаем всю высоту экрана */
  margin: 0;
  padding: 0;
}

/* Контейнер для страницы */
#app {
  display: flex;
  flex-direction: column;
  min-height: 100vh; /* Минимальная высота — вся высота экрана */
}

/* Футер с прямоугольником с закругленными углами */
.footer {
  background-color: transparent; /* Без фона на всю ширину */
  color: white;
  padding: 20px 0;
  text-align: center;
  margin-top: auto; /* Футер прижимается к низу */
  display: flex;
  justify-content: center;
}

.footer-content {
  background-color: #333; /* Цвет фона прямоугольника */
  color: white;
  padding: 20px;
  border-radius: 20px; /* Закругляем углы */
  width: 100%;
  max-width: 1200px; /* Максимальная ширина футера */
  box-sizing: border-box;
}

.social-links a {
  margin: 0 15px;
  text-decoration: none;
  color: white;
  font-size: 16px;
}

.social-links a:hover {
  color: #ff6347;
}
</style>
