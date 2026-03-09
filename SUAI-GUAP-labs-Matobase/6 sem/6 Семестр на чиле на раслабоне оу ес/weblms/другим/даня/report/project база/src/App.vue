<!-- src/App.vue -->
<template>
  <div id="app">
    <NavigationBar />
    <router-view />
    <SiteFooter />
  </div>
</template>

<script>
import NavigationBar from './components/NavigationBar.vue';  // Импортируем компонент NavigationBar
import SiteFooter from './components/SiteFooter.vue';  // Импортируем компонент SiteFooter

export default {
  name: 'App',
  components: {
    NavigationBar,  // Регистрация компонента NavigationBar
    SiteFooter  // Регистрация компонента SiteFooter
  }
};
</script>

<style>
/* Общие стили для приложения */
</style>
