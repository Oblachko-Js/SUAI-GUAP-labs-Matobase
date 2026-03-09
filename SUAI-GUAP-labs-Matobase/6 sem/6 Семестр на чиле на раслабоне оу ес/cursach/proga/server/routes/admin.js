const express = require("express");
const { requireAdmin } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Получить всех пользователей
router.get("/users", requireAdmin, async (req, res) => {
  try {
    const result = await db.query(`
      SELECT id, login, email, state, 
             (last_active > NOW() - INTERVAL '5 minutes') AS is_online
      FROM users
    `);
    res.status(200).json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении пользователей" });
  }
});

// Получить все задачи
router.get("/tasks", requireAdmin, async (req, res) => {
  try {
    const result = await db.query("SELECT * FROM tasks");
    res.status(200).json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении задач" });
  }
});

// Получить все привычки
router.get("/habits", requireAdmin, async (req, res) => {
  try {
    const result = await db.query("SELECT * FROM habits");
    res.status(200).json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении привычек" });
  }
});

// Получить всех персонажей
router.get("/characters", requireAdmin, async (req, res) => {
  try {
    const result = await db.query(`
      SELECT user_id, name, level, health, mana, experience, gold 
      FROM rpg_characters
    `);
    res.status(200).json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении персонажей" });
  }
});

// Удалить пользователя
router.delete("/users/:id", requireAdmin, async (req, res) => {
  const { id } = req.params; // Используем id для удаления
  try {
    await db.query("DELETE FROM users WHERE id = $1", [id]);
    res.status(200).send("Пользователь удалён");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при удалении пользователя" });
  }
});

// Удалить задачу
router.delete("/tasks/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  try {
    await db.query("DELETE FROM tasks WHERE user_id = $1", [id]);
    res.status(200).send("Задача удалена");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при удалении задачи" });
  }
});

// Удалить привычку
router.delete("/habits/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  try {
    await db.query("DELETE FROM habits WHERE user_id = $1", [id]);
    res.status(200).send("Привычка удалена");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при удалении привычки" });
  }
});

// Удалить персонажа
router.delete("/characters/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  try {
    await db.query("DELETE FROM rpg_characters WHERE user_id = $1", [id]);
    res.status(200).send("Персонаж удалён");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при удалении персонажа" });
  }
});

// Обновление данных пользователя
router.put("/users/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  const { field, value } = req.body;

  try {
    let query;
    switch (field) {
      case 1: // Логин
        query = "UPDATE users SET login = $1 WHERE id = $2";
        break;
      case 2: // Email
        query = "UPDATE users SET email = $1 WHERE id = $2";
        break;
      case 3: // Статус
        query = "UPDATE users SET state = $1 WHERE id = $2";
        break;
      default:
        throw new Error("Неверное поле");
    }

    await db.query(query, [value, id]);
    res.status(200).send("Данные обновлены");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при обновлении данных" });
  }
});

// Обновление данных задачи
router.put("/tasks/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  const { field, value } = req.body;

  try {
    let query;
    switch (field) {
      case 1: // Название задачи
        query = "UPDATE tasks SET name = $1 WHERE id = $2";
        break;
      case 2: // Статус задачи
        query = "UPDATE tasks SET completed = $1 WHERE id = $2";
        break;
      default:
        throw new Error("Неверное поле");
    }

    await db.query(query, [value, id]);
    res.status(200).send("Данные задачи обновлены");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при обновлении задачи" });
  }
});

// Обновление данных привычки
router.put("/habits/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  const { field, value } = req.body;

  try {
    let query;
    switch (field) {
      case 1: // Название привычки
        query = "UPDATE habits SET name = $1 WHERE id = $2";
        break;
      case 2: // Статус привычки
        query = "UPDATE habits SET status = $1 WHERE id = $2";
        break;
      default:
        throw new Error("Неверное поле");
    }

    await db.query(query, [value, id]);
    res.status(200).send("Данные привычки обновлены");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при обновлении привычки" });
  }
});

// Обновление данных персонажа
router.put("/characters/:id", requireAdmin, async (req, res) => {
  const { id } = req.params;
  const { field, value } = req.body;

  try {
    let query;
    switch (field) {
      case 1: // Имя персонажа
        query = "UPDATE rpg_characters SET name = $1 WHERE user_id = $2";
        break;
      case 2: // Уровень персонажа
        query = "UPDATE rpg_characters SET level = $1 WHERE user_id = $2";
        break;
      case 3: // Здоровье персонажа
        query = "UPDATE rpg_characters SET health = $1 WHERE user_id = $2";
        break;
      case 4: // Мана персонажа
        query = "UPDATE rpg_characters SET mana = $1 WHERE user_id = $2";
        break;
      case 5: // Опыт персонажа
        query = "UPDATE rpg_characters SET experience = $1 WHERE user_id = $2";
        break;
      case 6: // Золото персонажа
        query = "UPDATE rpg_characters SET gold = $1 WHERE user_id = $2";
        break;
      default:
        throw new Error("Неверное поле");
    }

    await db.query(query, [value, id]);
    res.status(200).send("Данные персонажа обновлены");
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при обновлении персонажа" });
  }
});

module.exports = router;
