const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Получить все предметы
router.get("/items", async (req, res) => {
  try {
    const result = await db.query("SELECT * FROM items");
    res.json(result.rows);
  } catch (err) {
    console.error("Ошибка при получении предметов:", err);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

// Маршрут для покупки предмета
router.post("/inventory", requireAuth, async (req, res) => {
  const { itemId, quantity } = req.body;
  const userId = req.session.user.id; // Используем userId из сессии

  try {
    // Получаем characterId из базы данных по userId
    const character = await db.query(
      "SELECT id, gold FROM rpg_characters WHERE user_id = $1",
      [userId]
    );

    if (!character.rows.length) {
      return res.status(404).json({ error: "Персонаж не найден" });
    }

    const characterId = character.rows[0].id; // Получаем characterId из результата запроса

    // Проверяем, существует ли предмет
    const item = await db.query("SELECT value FROM items WHERE id = $1", [
      itemId,
    ]);
    if (!item.rows.length) {
      return res.status(404).json({ error: "Предмет не найден" });
    }

    // Проверяем, есть ли уже этот предмет в инвентаре
    const existingItem = await db.query(
      "SELECT * FROM inventory WHERE character_id = $1 AND item_id = $2",
      [characterId, itemId]
    );

    if (existingItem.rows.length > 0) {
      return res.status(400).json({ error: "Предмет уже есть в инвентаре" });
    }

    // Проверяем, достаточно ли золота
    if (character.rows[0].gold < item.rows[0].value * quantity) {
      return res.status(400).json({ error: "Недостаточно золота" });
    }

    // Добавляем предмет в инвентарь
    await db.query(
      "INSERT INTO inventory (character_id, item_id, quantity) VALUES ($1, $2, $3)",
      [characterId, itemId, quantity]
    );

    // Вычитаем стоимость предмета из золота персонажа
    await db.query("UPDATE rpg_characters SET gold = gold - $1 WHERE id = $2", [
      item.rows[0].value * quantity,
      characterId,
    ]);

    res.json({ message: "Предмет куплен" });
  } catch (err) {
    console.error("Ошибка при покупке предмета:", err);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

module.exports = router;
