// src/router.js
import { createRouter, createWebHistory } from 'vue-router';
import HomePage from './views/HomePage.vue';
import TechnologyPage from './views/TechnologyPage.vue';
import IssuesPage from './views/IssuesPage.vue';
import ConclusionPage from './views/ConclusionPage.vue';

const routes = [
  {
    path: '/',
    name: 'home',
    component: HomePage,
    meta: {
      title: 'Главная страница',  // Заголовок для главной страницы
      description: 'Проект умного города: исследование технологий для умных и устойчивых городов.'
    }
  },
  {
    path: '/technology',
    name: 'technology',
    component: TechnologyPage,
    meta: {
      title: 'Технологии для умных городов',  // Заголовок для страницы технологий
      description: 'Узнайте, какие технологии делают города умными.'
    }
  },
  {
    path: '/issues',
    name: 'issues',
    component: IssuesPage,
    meta: {
      title: 'Проблемы умных городов',  // Заголовок для страницы проблем
      description: 'Разберемся, с какими проблемами сталкиваются умные города.'
    }
  },
  {
    path: '/conclusion',
    name: 'conclusion',
    component: ConclusionPage,
    meta: {
      title: 'Заключение',  // Заголовок для заключительной страницы
      description: 'Итоги исследования и решения для умных городов.'
    }
  }
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
});

// Обновление заголовка и мета-тегов при изменении маршрута
router.beforeEach((to, from, next) => {
  // Обновляем заголовок страницы
  document.title = to.meta.title || 'Проект Умный Город';  // Если заголовок не указан, будет использоваться значение по умолчанию

  // Мета-теги (например, описание)
  const metaDescription = document.querySelector('meta[name="description"]');
  if (metaDescription) {
    metaDescription.setAttribute('content', to.meta.description || '');
  } else {
    const newMetaDescription = document.createElement('meta');
    newMetaDescription.setAttribute('name', 'description');
    newMetaDescription.setAttribute('content', to.meta.description || '');
    document.head.appendChild(newMetaDescription);
  }

  next();
});

export default router;
