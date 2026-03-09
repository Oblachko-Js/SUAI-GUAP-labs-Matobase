//habits.js
const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Функция для проверки завершения задачи
async function checkAndCompleteTask(taskId, userId) {
  // Получаем количество невыполненных привычек для данной задачи
  const unfinishedHabits = await db.query(
    "SELECT COUNT(*) FROM habits WHERE task_id = $1 AND status != 'Выполнено'",
    [taskId]
  );

  if (unfinishedHabits.rows[0].count == 0) {
    // Если нет невыполненных привычек — обновляем задачу как завершенную
    await db.query(
      "UPDATE tasks SET completed = true WHERE id = $1 AND user_id = $2",
      [taskId, userId]
    );
  }
}

// Обновление статуса привычки и начисление награды
router.patch("/:id", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { id } = req.params;
  const { status } = req.body;

  try {
    // Обновляем статус привычки
    const result = await db.query(
      "UPDATE habits SET status = $1 WHERE id = $2 AND user_id = $3 RETURNING *",
      [status, id, userId]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Привычка не найдена" });
    }

    const habit = result.rows[0];

    // Начисляем награду за выполнение привычки
    if (status === "Выполнено") {
      //console.log(`Начисляем награду пользователю ${userId}`);
      await db.query(
        "UPDATE rpg_characters SET gold = gold + 10, experience = experience + 5 WHERE user_id = $1",
        [userId]
      );
    }

    // Проверяем, все ли привычки задачи выполнены
    await checkAndCompleteTask(habit.task_id, userId);

    res.json(habit);
  } catch (err) {
    console.error("Ошибка при обновлении привычки:", err);
    res.status(500).json({ error: "Ошибка при обновлении привычки" });
  }
});

// Удаление привычки
router.delete("/:id", requireAuth, async (req, res) => {
  const userId = req.session.user.id;
  const { id } = req.params;

  try {
    const result = await db.query(
      "DELETE FROM habits WHERE id = $1 AND user_id = $2 RETURNING *",
      [id, userId]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Привычка не найдена" });
    }

    res.json({ message: "Привычка удалена", deletedHabit: result.rows[0] });
  } catch (err) {
    console.error("Ошибка при удалении привычки:", err);
    res.status(500).json({ error: "Ошибка при удалении привычки" });
  }
});

module.exports = router;
