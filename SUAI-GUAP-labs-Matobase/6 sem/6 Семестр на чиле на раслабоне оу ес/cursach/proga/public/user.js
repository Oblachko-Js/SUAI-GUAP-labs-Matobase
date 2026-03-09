//user.js(public)
// Получаем элементы DOM
const characterInfo = document.getElementById("characterInfo");
const createCharacterBtn = document.getElementById("createCharacterBtn");
const characterForm = document.getElementById("characterForm");
const characterFormFields = document.getElementById("characterFormFields");
const cancelCharacterBtn = document.getElementById("cancelCharacterBtn");

// Получаем элементы DOM для задач и привычек
const tasksList = document.getElementById("tasksList");
const createTaskBtn = document.getElementById("createTaskBtn");
const taskForm = document.getElementById("taskForm");
const taskFormFields = document.getElementById("taskFormFields");

// Функция для загрузки данных о персонаже
async function loadCharacter() {
  try {
    const response = await fetch("/user/character", {
      method: "GET",
      credentials: "include", // Передаём куки сессии
    });
    const data = await response.json();

    if (response.ok) {
      // Отображаем информацию о персонаже
      characterInfo.innerHTML = `
        <p><strong>Имя:</strong> ${data.name}</p>
        <p><strong>Уровень:</strong> ${data.level}</p>
        <p><strong>Здоровье:</strong> ${data.health}</p>
        <p><strong>Мана:</strong> ${data.mana}</p>
        <p><strong>Опыт:</strong> ${data.experience}</p>
        <p><strong>Золото:</strong> ${data.gold}</p>
      `;
      // Проверяем, нужно ли повысить уровень
      checkLevelUp(data);
    } else {
      characterInfo.innerHTML = "<p>Персонаж не найден. Создайте нового!</p>";
    }
  } catch (err) {
    console.error("Ошибка при загрузке персонажа:", err);
    characterInfo.innerHTML = "<p>Ошибка при загрузке персонажа.</p>";
  }
}

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

// Функция проверки повышения уровня
async function checkLevelUp(character) {
  if (character.experience >= 100) {
    const newLevel = character.level + 1;
    const newExperience = character.experience - 100;

    try {
      await fetch("/user/character/level-up", {
        method: "PATCH",
        headers: { "Content-Type": "application/json" },
        credentials: "include",
        body: JSON.stringify({ level: newLevel, experience: newExperience }),
      });

      console.log("Персонаж повысил уровень!");
      loadCharacter(); // Перезагружаем данные о персонаже
    } catch (err) {
      console.error("Ошибка при повышении уровня:", err);
    }
  }
}

// Функция для создания/обновления персонажа
async function saveCharacter(event) {
  event.preventDefault();

  const name = document.getElementById("characterName").value;
  const level = document.getElementById("characterLevel").value;
  const health = document.getElementById("characterHealth").value;
  const mana = document.getElementById("characterMana").value;
  const experience = document.getElementById("characterExperience").value;
  const gold = document.getElementById("characterGold").value;

  try {
    const response = await fetch("/user/character", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include", // Передаем куки сессии
      body: JSON.stringify({ name, level, health, mana, experience, gold }),
    });

    if (response.ok) {
      alert("Персонаж успешно сохранен!");
      characterForm.style.display = "none";
      loadCharacter(); // Перезагружаем данные о персонаже
    } else {
      alert("Ошибка при сохранении персонажа.");
    }
  } catch (err) {
    console.error("Ошибка при сохранении персонажа:", err);
  }
}

// Показываем форму для создания/обновления персонажа
createCharacterBtn.addEventListener("click", () => {
  characterForm.style.display = "block";
});

// Скрываем форму при отмене
cancelCharacterBtn.addEventListener("click", () => {
  characterForm.style.display = "none";
});

// Обработка отправки формы
characterFormFields.addEventListener("submit", saveCharacter);

// Функция загрузки задач
async function loadTasks() {
  try {
    const response = await fetch("/tasks", {
      method: "GET",
      credentials: "include",
    });
    const tasks = await response.json();

    tasksList.innerHTML = ""; // Очищаем список перед обновлением
    const taskSelect = document.getElementById("taskSelect");
    taskSelect.innerHTML = '<option value="">-- Выберите задачу --</option>'; // Сбрасываем

    tasks.forEach((task) => {
      // Добавляем в выпадающий список
      const option = document.createElement("option");
      option.value = task.id;
      option.textContent = task.name;
      taskSelect.appendChild(option);

      // Создаём блок для задачи
      const taskItem = document.createElement("div");
      taskItem.classList.add("task-item");
      taskItem.dataset.taskId = task.id; // Присваиваем ID задачи в data-атрибут
      if (task.completed) taskItem.classList.add("completed");

      taskItem.innerHTML = `
                <h3>${task.name}</h3>
                <p>${task.description}</p>
                <p>Сложность: ${task.difficulty}</p>
                <p>Срок: ${new Date(task.due_date).toLocaleDateString()}</p>
                <p>Награда: ${task.rewardGold} золота, ${
        task.rewardExp
      } опыта</p>
                <button onclick="toggleHabits(${task.id})" id="toggle-habits-${
        task.id
      }">
                    Показать привычки
                </button>
                <div class="habits-list" id="habits-${
                  task.id
                }" style="display: none;"></div>
                <button onclick="addHabit(${
                  task.id
                })">Добавить привычку</button>
                <button onclick="deleteTask(${
                  task.id
                })" class="delete-task-btn">Удалить задачу</button>
            `;

      tasksList.appendChild(taskItem);
    });
  } catch (err) {
    console.error("Ошибка при загрузке задач:", err);
  }
}

async function toggleHabits(taskId) {
  const habitsList = document.getElementById(`habits-${taskId}`);
  const toggleButton = document.getElementById(`toggle-habits-${taskId}`);

  if (habitsList.style.display === "none") {
    // Разворачиваем список, если он скрыт
    habitsList.style.display = "block";
    toggleButton.textContent = "Скрыть привычки";
    await loadHabits(taskId); // Загружаем привычки
  } else {
    // Сворачиваем список, если он уже открыт
    habitsList.style.display = "none";
    toggleButton.textContent = "Показать привычки";
  }
}

// Функция загрузки привычек для задачи
async function loadHabits(taskId) {
  try {
    const response = await fetch(`/tasks/${taskId}/habits`, {
      method: "GET",
      credentials: "include",
    });

    if (!response.ok) {
      throw new Error(`Ошибка ${response.status}: ${response.statusText}`);
    }

    const habits = await response.json();
    const habitsList = document.getElementById(`habits-${taskId}`);
    habitsList.innerHTML = "";

    if (!habits.length) {
      habitsList.innerHTML = "<p>Нет привычек.</p>";
      return;
    }

    habits.forEach((habit) => {
      const habitItem = document.createElement("div");
      habitItem.classList.add("habit-item");
      if (habit.status === "Выполнено") habitItem.classList.add("completed");

      habitItem.innerHTML = `
          <span><strong>${habit.name}</strong></span>
          <p>${habit.description}</p>
          <p>Награда: ${habit.rewardGold} золота, ${habit.rewardExp} опыта</p>
          <input type="checkbox" 
                 ${habit.status === "Выполнено" ? "checked" : ""} 
                 onchange="toggleHabit(${habit.id}, ${taskId}, this.checked)">
          <button onclick="deleteHabit(${
            habit.id
          }, ${taskId})" class="delete-habit-btn">Удалить</button>
        `;

      habitsList.appendChild(habitItem);
    });
  } catch (err) {
    console.error("Ошибка при загрузке привычек:", err);
  }
}

// Функция создания новой задачи
async function createTask(event) {
  event.preventDefault();

  const name = document.getElementById("taskName").value;
  const description = document.getElementById("taskDescription").value;
  const difficulty = document.getElementById("taskDifficulty").value;
  const due_date = document.getElementById("taskDueDate").value;

  try {
    const taskResponse = await fetch("/tasks/create", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({ name, description, difficulty, due_date }),
    });

    if (taskResponse.ok) {
      alert("Задача успешно создана!");
      taskForm.style.display = "none";
      loadTasks();
    } else {
      alert("Ошибка при создании задачи.");
    }
  } catch (err) {
    console.error("Ошибка при создании задачи:", err);
  }
}

// Функция добавления привычки в задачу
async function addHabit(taskId) {
  const habitName = prompt("Введите название привычки:");
  if (!habitName) return;

  const habitDescription = prompt("Введите описание привычки:") || ""; // Описание можно оставить пустым

  try {
    const response = await fetch(`/tasks/${taskId}/habit`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({
        name: habitName,
        description: habitDescription, // Передаём описание привычки
        difficulty: "Средняя",
      }),
    });

    if (!response.ok) {
      throw new Error("Ошибка при создании привычки.");
    }

    alert("Привычка успешно добавлена!");
    loadHabits(taskId); // Обновляем список привычек
  } catch (err) {
    console.error("Ошибка при добавлении привычки:", err);
    alert("Не удалось добавить привычку.");
  }
}

// Функция отметки выполнения привычки
async function toggleHabit(habitId, taskId, isChecked) {
  try {
    await fetch(`/habits/${habitId}`, {
      // Здесь вместо taskId используем habitId
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({
        status: isChecked ? "Выполнено" : "Не выполнено",
      }),
    });

    loadHabits(taskId); // Перезагружаем привычки после изменения
    checkTaskCompletion(taskId);
  } catch (err) {
    console.error("Ошибка при изменении статуса привычки:", err);
  }
}

// Проверка выполнения всех привычек в задаче
async function checkTaskCompletion(taskId) {
  try {
    const response = await fetch(`/tasks/${taskId}/habits`, {
      method: "GET",
      credentials: "include",
    });

    //console.log("Ответ сервера:", response);

    const habits = await response.json();

    const allCompleted = habits.every((habit) => habit.status === "Выполнено");

    if (allCompleted) {
      await fetch(`/tasks/${taskId}`, {
        method: "PATCH",
        headers: { "Content-Type": "application/json" },
        credentials: "include",
        body: JSON.stringify({ completed: true }),
      });

      loadTasks();
    }
  } catch (err) {
    console.error("Ошибка при проверке выполнения задачи:", err);
  }
}

async function deleteTask(taskId) {
  if (!confirm("Вы уверены, что хотите удалить эту задачу?")) return;

  try {
    const response = await fetch(`/tasks/${taskId}`, {
      method: "DELETE",
      credentials: "include",
    });

    if (!response.ok) throw new Error("Ошибка при удалении задачи.");

    alert("Задача удалена!");
    loadTasks(); // Перезагрузка списка задач
  } catch (err) {
    console.error("Ошибка при удалении задачи:", err);
    alert("Не удалось удалить задачу.");
  }
}

async function deleteHabit(habitId, taskId) {
  if (!confirm("Вы уверены, что хотите удалить эту привычку?")) return;

  try {
    const response = await fetch(`/habits/${habitId}`, {
      method: "DELETE",
      credentials: "include",
    });

    if (!response.ok) throw new Error("Ошибка при удалении привычки.");

    alert("Привычка удалена!");
    loadHabits(taskId); // Перезагрузка списка привычек
  } catch (err) {
    console.error("Ошибка при удалении привычки:", err);
    alert("Не удалось удалить привычку.");
  }
}

// Обработчик отправки формы для задачи
taskFormFields.addEventListener("submit", createTask);

// Показываем форму для создания задачи
createTaskBtn.addEventListener("click", () => {
  taskForm.style.display = "block";
});

// Скрываем форму при нажатии "Отмена"
document.getElementById("cancelTaskBtn").addEventListener("click", () => {
  taskForm.style.display = "none";
});

// Фильтрация задач при выборе в select
document.getElementById("taskSelect").addEventListener("change", function () {
  const selectedTaskId = this.value;
  const taskItems = document.querySelectorAll(".task-item");

  taskItems.forEach((taskItem) => {
    const taskId = taskItem.dataset.taskId;

    if (selectedTaskId === "" || taskId === selectedTaskId) {
      taskItem.style.display = "block";
    } else {
      taskItem.style.display = "none";
    }
  });
});

// Функция для загрузки предметов из магазина
async function fetchShopItems() {
  try {
    const response = await fetch("/api/items", {
      method: "GET",
      credentials: "include",
    });
    const items = await response.json();
    return items;
  } catch (err) {
    console.error("Ошибка при загрузке предметов магазина:", err);
    return [];
  }
}

// Функция для отображения предметов в магазине
async function displayShopItems() {
  const items = await fetchShopItems();
  const shopItems = document.getElementById("shopItems");

  shopItems.innerHTML = items
    .map(
      (item) => `
      <div class="shop-item" data-id="${item.id}">
          <img src="${item.image_path}" alt="${item.name}">
          <h4>${item.name}</h4>
          <p>Тип: ${item.type}</p>
          <p>Эффект: ${item.effect || "Нет эффекта"}</p>
          <p>Цена: ${item.value} золота</p>
          <button onclick="buyItem(${item.id})">Купить</button>
      </div>
  `
    )
    .join("");
}

async function buyItem(itemId) {
  try {
    const response = await fetch("/api/inventory", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({ itemId, quantity: 1 }), // Указываем количество предметов
    });

    const data = await response.json(); // Получаем ответ от сервера

    if (response.ok) {
      alert("Предмет куплен!");
      loadCharacter(); // Обновляем данные персонажа (золото)
      displayShopItems(); // Обновляем магазин
      displayInventoryItems();
    } else {
      // Обрабатываем ошибку, если сервер вернул статус 400
      if (data.error === "Недостаточно золота") {
        alert("Недостаточно золота для покупки предмета.");
      } else if (data.error === "Предмет уже есть в инвентаре") {
        alert("Этот предмет уже есть в вашем инвентаре.");
      } else {
        alert("Произошла ошибка при покупке предмета.");
      }
    }
  } catch (err) {
    console.error("Ошибка при покупке предмета:", err);
    alert("Ошибка при покупке предмета.");
  }
}

// Обработчик для кнопки сворачивания/разворачивания магазина
document
  .getElementById("toggleShopButton")
  .addEventListener("click", function () {
    const shopSection = document.getElementById("shopSection");
    const toggleButton = document.getElementById("toggleShopButton");

    // Переключаем класс collapsed
    shopSection.classList.toggle("collapsed");

    // Меняем текст кнопки в зависимости от состояния
    if (shopSection.classList.contains("collapsed")) {
      toggleButton.textContent = "▲"; // Показываем стрелку вверх, если блок свернут
    } else {
      toggleButton.textContent = "▼"; // Показываем стрелку вниз, если блок развернут
    }
  });

// Функция для загрузки предметов из инвентаря
async function fetchInventoryItems() {
  try {
    const response = await fetch("/api/inventory", {
      method: "GET",
      credentials: "include",
    });

    if (!response.ok) {
      throw new Error(`Ошибка ${response.status}: ${response.statusText}`);
    }

    const items = await response.json();
    return items;
  } catch (err) {
    console.error("Ошибка при загрузке предметов инвентаря:", err);
    return [];
  }
}

// Функция для отображения предметов в инвентаре
async function displayInventoryItems() {
  const items = await fetchInventoryItems();
  const inventoryItems = document.getElementById("inventoryItems");
  const equippedItemsOverlay = document.getElementById("equippedItemsOverlay");

  // Очищаем контейнер с надетыми предметами
  equippedItemsOverlay.innerHTML = "";

  // Отображаем предметы в инвентаре
  inventoryItems.innerHTML = items
    .map(
      (item) => `
      <div class="inventory-item" data-id="${item.item_id}">
          <img src="${item.image_path}" alt="${item.name}">
          <h4>${item.name}</h4>
          <p>Тип: ${item.type}</p>
          <p>Эффект: ${item.effect || "Нет эффекта"}</p>
          <input type="checkbox" 
                 ${item.is_equipped ? "checked" : ""} 
                 onchange="equipItem(${item.item_id}, this.checked)">
      </div>
  `
    )
    .join("");

  // Отображаем надетые предметы поверх изображения персонажа
  items.forEach((item) => {
    if (item.is_equipped) {
      const equippedItem = document.createElement("img");
      equippedItem.src = item.image_path;
      equippedItem.alt = item.name;
      equippedItem.title = item.name;
      equippedItem.style.position = "absolute";
      equippedItem.style.top = "0";
      equippedItem.style.left = "0";
      equippedItem.style.width = "100%"; // Предметы такого же размера, как персонаж
      equippedItem.style.height = "auto";
      equippedItemsOverlay.appendChild(equippedItem);
    }
  });
}

// Функция для "надевания" предмета на персонажа
async function equipItem(itemId, isChecked) {
  try {
    const response = await fetch("/api/equip", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({ itemId, equip: isChecked }),
    });

    if (response.ok) {
      const data = await response.json();
      alert(data.message); // "Предмет надет!" или "Предмет снят!"

      // Обновляем состояние checkbox
      const checkbox = document.querySelector(
        `.inventory-item[data-id="${itemId}"] input[type="checkbox"]`
      );
      if (checkbox) {
        checkbox.checked = data.is_equipped;
      }

      // Обновляем отображение надетых предметов
      displayInventoryItems();
    } else {
      alert("Ошибка при применении предмета.");
    }
  } catch (err) {
    console.error("Ошибка при применении предмета:", err);
    alert("Ошибка при применении предмета.");
  }
}

// Обработчик для кнопки сворачивания/разворачивания инвентаря
document
  .getElementById("toggleInventoryButton")
  .addEventListener("click", function () {
    const inventorySection = document.getElementById("inventorySection");
    const toggleButton = document.getElementById("toggleInventoryButton");

    // Переключаем класс collapsed
    inventorySection.classList.toggle("collapsed");

    // Меняем текст кнопки в зависимости от состояния
    if (inventorySection.classList.contains("collapsed")) {
      toggleButton.textContent = "▲"; // Показываем стрелку вверх, если блок свернут
    } else {
      toggleButton.textContent = "▼"; // Показываем стрелку вниз, если блок развернут
    }
  });

// Инициализация инвентаря
window.addEventListener("load", () => {
  displayShopItems();
  displayInventoryItems();
});

// Загружаем данные о персонаже и задачи при загрузке страницы
window.onload = function () {
  // Вызываем функцию сразу при загрузке
  checkAuth();
  loadCharacter();
  // Обновляем данные персонажа каждую секунду
  setInterval(loadCharacter, 1000);
  loadTasks();
  displayShopItems();
  displayInventoryItems();
};
