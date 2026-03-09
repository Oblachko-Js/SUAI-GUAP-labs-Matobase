//tasks.js
const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware"); // Добавляем защиту маршрутов
const db = require("../db");
const router = express.Router();

// Создание новой задачи
router.post("/create", requireAuth, async (req, res) => {
  const userId = req.session.user.id; // Берем user_id из сессии
  const { name, description, difficulty, due_date } = req.body;

  try {
    const result = await db.query(
      "INSERT INTO tasks (user_id, name, description, difficulty, due_date) VALUES ($1, $2, $3, $4, $5) RETURNING *",
      [userId, name, description, difficulty, due_date]
    );
    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при создании задачи" });
  }
});

// Добавление привычки в задачу
router.post("/:taskId/habit", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { taskId } = req.params;
  const { name, description, difficulty } = req.body;

  try {
    // Проверяем, существует ли задача
    const taskCheck = await db.query(
      "SELECT id FROM tasks WHERE id = $1 AND user_id = $2",
      [taskId, userId]
    );

    if (taskCheck.rows.length === 0) {
      return res.status(404).json({ error: "Задача не найдена" });
    }

    const result = await db.query(
      "INSERT INTO habits (user_id, task_id, name, description, difficulty) VALUES ($1, $2, $3, $4, $5) RETURNING *",
      [userId, taskId, name, description, difficulty]
    );

    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при добавлении привычки" });
  }
});

// Получение всех задач пользователя с их привычками
router.get("/", requireAuth, async (req, res) => {
  const userId = req.session.user.id; // Берем user_id из сессии
  try {
    const tasks = await db.query(
      "SELECT * FROM tasks WHERE user_id = $1 ORDER BY created_at DESC",
      [userId]
    );

    const taskList = await Promise.all(
      tasks.rows.map(async (task) => {
        const habits = await db.query(
          "SELECT * FROM habits WHERE task_id = $1",
          [task.id]
        );

        // Добавляем информацию о награде
        let rewardGold = 0;
        let rewardExp = 0;

        switch (task.difficulty) {
          case "Легкая":
            rewardGold = 20;
            rewardExp = 10;
            break;
          case "Средняя":
            rewardGold = 50;
            rewardExp = 25;
            break;
          case "Сложная":
            rewardGold = 100;
            rewardExp = 50;
            break;
        }

        return { ...task, habits: habits.rows, rewardGold, rewardExp };
      })
    );

    res.json(taskList);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при загрузке задач" });
  }
});

// Получение привычек для конкретной задачи
router.get("/:taskId/habits", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { taskId } = req.params;

  try {
    // Проверяем, существует ли задача и принадлежит ли пользователю
    const taskCheck = await db.query(
      "SELECT id FROM tasks WHERE id = $1 AND user_id = $2",
      [taskId, userId]
    );

    if (taskCheck.rows.length === 0) {
      return res
        .status(404)
        .json({ error: "Задача не найдена или не принадлежит вам" });
    }

    const habits = await db.query("SELECT * FROM habits WHERE task_id = $1", [
      taskId,
    ]);

    // Добавляем информацию о награде
    const habitsWithRewards = habits.rows.map((habit) => ({
      ...habit,
      rewardGold: 10, // За выполнение привычки начисляется 10 золота
      rewardExp: 5, // За выполнение привычки начисляется 5 опыта
    }));

    res.json(habitsWithRewards);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при загрузке привычек" });
  }
});

// Обновление статуса задачи и начисление награды
router.patch("/:taskId", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { taskId } = req.params;
  const { completed } = req.body;

  try {
    const result = await db.query(
      "UPDATE tasks SET completed = $1 WHERE id = $2 AND user_id = $3 RETURNING *",
      [completed, taskId, userId]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Задача не найдена" });
    }

    if (completed) {
      // Получаем сложность задачи
      const task = result.rows[0];
      let rewardGold = 0;
      let rewardExp = 0;

      switch (task.difficulty) {
        case "Легкая":
          rewardGold = 20;
          rewardExp = 10;
          break;
        case "Средняя":
          rewardGold = 50;
          rewardExp = 25;
          break;
        case "Сложная":
          rewardGold = 100;
          rewardExp = 50;
          break;
      }

      // Начисляем награду
      await db.query(
        "UPDATE rpg_characters SET gold = gold + $1, experience = experience + $2 WHERE user_id = $3",
        [rewardGold, rewardExp, userId]
      );
    }

    res.json(result.rows[0]);
  } catch (err) {
    console.error("Ошибка при обновлении задачи:", err);
    res.status(500).json({ error: "Ошибка при обновлении задачи" });
  }
});

// Удаление задачи
router.delete("/:taskId", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { taskId } = req.params;

  try {
    // Проверяем, существует ли задача и принадлежит ли пользователю
    const taskCheck = await db.query(
      "SELECT id FROM tasks WHERE id = $1 AND user_id = $2",
      [taskId, userId]
    );

    if (taskCheck.rows.length === 0) {
      return res.status(404).json({ error: "Задача не найдена" });
    }

    // Удаляем связанные привычки
    await db.query("DELETE FROM habits WHERE task_id = $1", [taskId]);

    // Удаляем саму задачу
    const result = await db.query(
      "DELETE FROM tasks WHERE id = $1 AND user_id = $2 RETURNING *",
      [taskId, userId]
    );

    res.json({ message: "Задача удалена", deletedTask: result.rows[0] });
  } catch (err) {
    console.error("Ошибка при удалении задачи:", err);
    res.status(500).json({ error: "Ошибка при удалении задачи" });
  }
});

module.exports = router;
