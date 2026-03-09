//user.js(routes)
const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Создание или обновление персонажа (только для авторизованных пользователей)
router.post("/character", requireAuth, async (req, res) => {
  const userId = req.session.user.id; // Берем userId из сессии
  const { name, level, health, mana, experience, gold } = req.body;

  try {
    // Проверяем, есть ли уже персонаж у пользователя
    const existingCharacter = await db.query(
      "SELECT * FROM rpg_characters WHERE user_id = $1",
      [userId]
    );

    if (existingCharacter.rows.length > 0) {
      // Если персонаж уже есть, обновляем его
      const result = await db.query(
        `UPDATE rpg_characters 
         SET name = $1, level = $2, health = $3, mana = $4, experience = $5, gold = $6 
         WHERE user_id = $7 RETURNING *`,
        [name, level, health, mana, experience, gold, userId]
      );
      res.status(200).json(result.rows[0]);
    } else {
      // Если персонажа нет, создаем нового
      const result = await db.query(
        `INSERT INTO rpg_characters (user_id, name, level, health, mana, experience, gold) 
         VALUES ($1, $2, $3, $4, $5, $6, $7) RETURNING *`,
        [userId, name, level, health, mana, experience, gold]
      );
      res.status(201).json(result.rows[0]);
    }
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при создании/обновлении персонажа" });
  }
});

// Получение персонажа (только для авторизованных пользователей)
router.get("/character", requireAuth, async (req, res) => {
  const userId = req.session.user.id; // Берем userId из сессии

  try {
    const result = await db.query(
      "SELECT * FROM rpg_characters WHERE user_id = $1",
      [userId]
    );

    if (result.rows.length > 0) {
      res.status(200).json(result.rows[0]);
    } else {
      res.status(404).json({ error: "Персонаж не найден" });
    }
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении персонажа" });
  }
});

// Обновление уровня персонажа
router.patch("/character/level-up", requireAuth, async (req, res) => {
  try {
    const { level, experience } = req.body;
    const userId = req.session.user.id; // Используем userId из сессии

    await db.query(
      "UPDATE rpg_characters SET level = $1, experience = $2 WHERE user_id = $3",
      [level, experience, userId]
    );

    res.json({ message: "Уровень повышен!" });
  } catch (err) {
    console.error("Ошибка при обновлении уровня:", err);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

module.exports = router;
