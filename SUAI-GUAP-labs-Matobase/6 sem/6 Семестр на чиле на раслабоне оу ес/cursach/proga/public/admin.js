// Проверка авторизации и прав администратора
async function checkAuth() {
  try {
    // Проверяем авторизацию и получаем данные о пользователе
    const response = await fetch("/auth/check", {
      method: "GET",
      credentials: "include",
    });

    if (!response.ok) {
      window.location.href = "/"; // Перенаправляем на главную, если не авторизован
      return;
    }

    const data = await response.json();

    // Проверяем, является ли пользователь администратором
    if (data.user.login !== "admin") {
      window.location.href = "/"; // Перенаправляем на главную, если пользователь не admin
    }
  } catch (error) {
    console.error("Ошибка при проверке авторизации:", error);
    window.location.href = "/"; // Перенаправляем на главную в случае ошибки
  }
}

// Загрузка данных
async function loadData() {
  await checkAuth();

  try {
    const usersResponse = await fetch("/admin/users", {
      credentials: "include",
    });
    const users = await usersResponse.json();
    renderTable(
      "usersTable",
      users,
      (user) => `
        <td>${user.id}</td>
        <td>${user.login}</td>
        <td>${user.email}</td>
        <td>${user.is_online ? "Онлайн" : "Офлайн"}</td>
      `
    );

    const tasksResponse = await fetch("/admin/tasks", {
      credentials: "include",
    });
    const tasks = await tasksResponse.json();
    renderTable(
      "tasksTable",
      tasks,
      (task) => `
        <td>${task.id}</td>
        <td>${task.name}</td>
        <td>${task.completed ? "Выполнено" : "Не выполнено"}</td>
      `
    );

    const habitsResponse = await fetch("/admin/habits", {
      credentials: "include",
    });
    const habits = await habitsResponse.json();
    renderTable(
      "habitsTable",
      habits,
      (habit) => `
        <td>${habit.id}</td>
        <td>${habit.name}</td>
        <td>${habit.status}</td>
      `
    );

    const charactersResponse = await fetch("/admin/characters", {
      credentials: "include",
    });
    const characters = await charactersResponse.json();
    renderTable(
      "charactersTable",
      characters,
      (character) => `
        <td>${character.user_id}</td>
        <td>${character.name}</td>
        <td>${character.level}</td>
        <td>${character.health}</td>
        <td>${character.mana}</td>
        <td>${character.experience}</td>
        <td>${character.gold}</td>
      `
    );
  } catch (err) {
    console.error("Ошибка при загрузке данных:", err);
  }
}

// Функция для активации редактирования ячейки
function enableEditing(cell, value, updateCallback) {
  cell.innerHTML = `<input type="text" value="${value}" />`;
  const input = cell.querySelector("input");
  input.focus();

  // Сохраняем изменения при потере фокуса или нажатии Enter
  input.addEventListener("blur", () => {
    updateCallback(input.value);
  });

  input.addEventListener("keyup", (event) => {
    if (event.key === "Enter") {
      updateCallback(input.value);
    }
  });
}

// Функция для обновления данных на сервере
async function updateData(tableId, id, field, value) {
  try {
    const endpoint = `/admin/${tableId.replace("Table", "")}/${id}`;
    const response = await fetch(endpoint, {
      method: "PUT",
      credentials: "include",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ field, value }),
    });

    if (response.ok) {
      loadData(); // Перезагружаем данные после успешного обновления
    } else {
      alert("Ошибка при обновлении данных");
    }
  } catch (err) {
    console.error("Ошибка при обновлении данных:", err);
  }
}

// Модифицируем renderTable для добавления редактирования
function renderTable(tableId, data, rowTemplate) {
  const tableBody = document.querySelector(`#${tableId} tbody`);
  tableBody.innerHTML = data
    .map((row) => {
      return `
      <tr>
        ${rowTemplate(row)}
        <td><button class="deleteBtn" data-id="${
          tableId === "usersTable" ? row.id : row.user_id
        }">X</button></td>
      </tr>
    `;
    })
    .join("");

  // Добавляем обработчики событий для редактирования ячеек
  const editableCells = tableBody.querySelectorAll("td:not(:last-child)");
  editableCells.forEach((cell) => {
    cell.addEventListener("dblclick", () => {
      const row = cell.closest("tr");
      const id = row.querySelector(".deleteBtn").dataset.id;
      const field = cell.cellIndex; // Индекс столбца (можно заменить на data-атрибуты)
      const value = cell.textContent;

      enableEditing(cell, value, (newValue) => {
        updateData(tableId, id, field, newValue);
      });
    });
  });

  // Добавляем обработчики событий для кнопок удаления
  const deleteButtons = tableBody.querySelectorAll(".deleteBtn");
  deleteButtons.forEach((btn) => {
    btn.addEventListener("click", (event) => {
      const id = event.target.dataset.id;
      if (id) {
        deleteRow(tableId, id);
      } else {
        console.error("id не найден");
      }
    });
  });
}

// Функция для удаления строки
async function deleteRow(tableId, id) {
  // Показываем предупреждение перед удалением
  const confirmDelete = window.confirm(
    "Вы уверены, что хотите удалить эту запись?"
  );
  if (!confirmDelete) {
    return; // Если пользователь не подтвердил, отменяем удаление
  }

  try {
    // Для таблицы users используем id, для других таблиц - user_id
    const endpoint =
      tableId === "usersTable"
        ? `/admin/users/${id}` // Для users используем id
        : `/admin/${tableId.replace("Table", "")}/${id}`; // Для остальных - user_id

    const response = await fetch(endpoint, {
      method: "DELETE",
      credentials: "include",
    });

    if (response.ok) {
      loadData(); // Перезагружаем данные
    } else {
      alert("Ошибка при удалении");
    }
  } catch (err) {
    console.error("Ошибка при удалении строки:", err);
  }
}

// Загрузка данных при загрузке страницы
window.onload = loadData;
