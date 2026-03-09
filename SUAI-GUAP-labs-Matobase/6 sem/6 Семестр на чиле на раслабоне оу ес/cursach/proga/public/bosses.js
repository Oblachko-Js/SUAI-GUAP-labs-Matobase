// Проверка авторизации перед загрузкой страницы
async function checkAuth() {
  try {
    const response = await fetch("/auth/check", {
      method: "GET",
      credentials: "include",
    });

    if (!response.ok) {
      window.location.href = "/"; // Перенаправляем на главную
    }
  } catch (error) {
    console.error("Ошибка при проверке авторизации:", error);
    window.location.href = "/";
  }
}

async function loadBosses() {
  // Проверяем авторизацию перед загрузкой данных
  await checkAuth();

  try {
    const response = await fetch("/bosses", {
      credentials: "include",
    });

    if (!response.ok) {
      throw new Error(`Ошибка: ${response.status} ${response.statusText}`);
    }

    const bosses = await response.json(); // Парсим JSON
    renderBosses(bosses);
  } catch (err) {
    console.error("Ошибка при загрузке боссов:", err);
  }
}

function renderBosses(bosses) {
  const bossesList = document.getElementById("bossesList");
  bossesList.innerHTML = bosses
    .map((boss) => {
      return `
                  <div class="boss-card">
                      <img src="images/${boss.name.toLowerCase()}.jpg" alt="${
        boss.name
      }" />
                      <h3>${boss.name}</h3>
                      <p><strong>Здоровье:</strong> ${boss.health}</p>
                      <p><strong>Награда:</strong> ${
                        boss.reward_experience
                      } опыта и ${boss.reward_gold} золота</p>
                      <button class="fight-btn" data-id="${
                        boss.id
                      }">Сражаться</button>
                  </div>
              `;
    })
    .join("");

  // Добавляем обработчики событий для кнопок "Сражаться"
  const fightButtons = bossesList.querySelectorAll(".fight-btn");
  fightButtons.forEach((btn) => {
    btn.addEventListener("click", async (event) => {
      const bossId = event.target.dataset.id;
      const bossCard = event.target.closest(".boss-card"); // Находим карточку босса

      try {
        // Получаем текущую ману персонажа
        const characterResponse = await fetch("/user/character", {
          method: "GET",
          credentials: "include",
        });

        if (!characterResponse.ok) {
          throw new Error("Ошибка при загрузке данных персонажа");
        }

        const character = await characterResponse.json();

        // Проверяем ману перед атакой
        if (character.mana < 100) {
          throw new Error("Недостаточно маны для атаки");
        }

        // Если маны достаточно, отправляем запрос на сервер
        const response = await fetch(`/bosses/${bossId}/fight`, {
          method: "POST",
          credentials: "include",
        });

        if (!response.ok) {
          const errorData = await response.json();
          throw new Error(errorData.error || "Ошибка при сражении");
        }

        const result = await response.json();

        // Обновляем здоровье босса в карточке
        const bossHealthElement = bossCard.querySelector("p:nth-of-type(1)"); // Элемент с здоровьем босса
        bossHealthElement.textContent = `Здоровье: ${result.bossHealth}`;

        // Показываем результат атаки
        alert(
          `Вы нанесли ${result.damage} урона! У босса осталось ${result.bossHealth} здоровья.`
        );

        // Если босс побеждён
        if (result.bossHealth <= 0) {
          alert(
            `Босс побеждён! Вы получили ${result.reward_experience} опыта и ${result.reward_gold} золота.`
          );
          loadBosses(); // Перезагружаем список боссов
        }

        updateManaDisplay();
      } catch (err) {
        console.error("Ошибка при сражении:", err);
        alert(err.message); // Показываем конкретное сообщение об ошибке
      }
    });
  });
}

// Функция для обновления отображения маны
async function updateManaDisplay() {
  try {
    const response = await fetch("/user/character", {
      method: "GET",
      credentials: "include",
    });

    if (!response.ok) {
      throw new Error("Ошибка при загрузке данных персонажа");
    }

    const character = await response.json();

    // Обновляем отображение маны
    document.getElementById("currentMana").textContent = character.mana;

    // Рассчитываем ману за клик
    const manaPerClick = 1 + (character.level - 1) * 0.2;
    document.getElementById("manaPerClick").textContent =
      manaPerClick.toFixed(1);
  } catch (err) {
    console.error("Ошибка при обновлении отображения маны:", err);
  }
}

// Функция для восстановления маны
async function restoreMana() {
  try {
    const response = await fetch("/bosses/restore-mana", {
      method: "POST",
      credentials: "include",
    });

    if (!response.ok) {
      throw new Error("Ошибка при восстановлении маны");
    }

    const result = await response.json();

    // Обновляем отображение маны
    document.getElementById("currentMana").textContent = result.mana;

    // Обновляем ману за клик
    const manaPerClick = 1 + (result.level - 1) * 0.2;
    document.getElementById("manaPerClick").textContent =
      manaPerClick.toFixed(1);
  } catch (err) {
    console.error("Ошибка при восстановлении маны:", err);
    alert("Ошибка при восстановлении маны");
  }
}

// Обработчик клика по кнопке восстановления маны
document
  .getElementById("restoreManaBtn")
  .addEventListener("click", restoreMana);

// Инициализация отображения маны при загрузке страницы
window.onload = function () {
  loadBosses();
  updateManaDisplay();
};
