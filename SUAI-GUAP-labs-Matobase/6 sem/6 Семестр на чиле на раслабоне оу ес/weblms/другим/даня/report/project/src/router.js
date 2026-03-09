// src/router.js
import { createRouter, createWebHistory } from "vue-router";
import HomePage from "./views/HomePage.vue";
import TechnologyPage from "./views/TechnologyPage.vue";
import IssuesPage from "./views/IssuesPage.vue";
import ConclusionPage from "./views/ConclusionPage.vue";

const routes = [
  {
    path: "/",
    name: "home",
    component: HomePage,
    meta: {
      title: "Характеристики линий связи", // Заголовок для главной страницы
      description:
        "Обзор параметров линий связи: полоса пропускания, затухание, BER, задержки.",
    },
  },
  {
    path: "/technology",
    name: "technology",
    component: TechnologyPage,
    meta: {
      title: "Параметры и виды линий связи", // Заголовок для страницы технологий
      description:
        "Полоса пропускания, затухание, шум и помехи, задержка, BER; медь, оптика, радио.",
    },
  },
  {
    path: "/issues",
    name: "issues",
    component: IssuesPage,
    meta: {
      title: "Проблемы и искажения в линиях связи", // Заголовок для страницы проблем
      description:
        "Кросс-наводки, многолучевость, дисперсия, отражения, затухание и способы борьбы.",
    },
  },
  {
    path: "/conclusion",
    name: "conclusion",
    component: ConclusionPage,
    meta: {
      title: "Заключение по линиям связи", // Заголовок для заключительной страницы
      description:
        "Основные выводы по характеристикам линий связи и рекомендации по выбору среды.",
    },
  },
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
});

// Обновление заголовка и мета-тегов при изменении маршрута
router.beforeEach((to, from, next) => {
  // Обновляем заголовок страницы
  document.title = to.meta.title || "Проект Характеристики линий связи"; // Если заголовок не указан, будет использоваться значение по умолчанию

  // Мета-теги (например, описание)
  const metaDescription = document.querySelector('meta[name="description"]');
  if (metaDescription) {
    metaDescription.setAttribute("content", to.meta.description || "");
  } else {
    const newMetaDescription = document.createElement("meta");
    newMetaDescription.setAttribute("name", "description");
    newMetaDescription.setAttribute("content", to.meta.description || "");
    document.head.appendChild(newMetaDescription);
  }

  next();
});

export default router;
