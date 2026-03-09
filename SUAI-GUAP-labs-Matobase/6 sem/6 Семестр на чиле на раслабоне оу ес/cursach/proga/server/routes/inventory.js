const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Получить все предметы из инвентаря пользователя
router.get("/inventory", requireAuth, async (req, res) => {
  try {
    const userId = req.session.user.id; // Получаем userId из сессии

    // Получаем characterId из базы данных по userId
    const character = await db.query(
      "SELECT id FROM rpg_characters WHERE user_id = $1",
      [userId]
    );

    if (!character.rows.length) {
      return res.status(404).json({ error: "Персонаж не найден" });
    }

    const characterId = character.rows[0].id; // Получаем characterId

    // Получаем все предметы из инвентаря для данного персонажа
    const result = await db.query(
      `SELECT inventory.id, inventory.item_id, items.name, items.image_path, items.type, items.effect, inventory.quantity, inventory.is_equipped 
         FROM inventory 
         JOIN items ON inventory.item_id = items.id 
         WHERE inventory.character_id = $1`,
      [characterId] // Передаем characterId как параметр
    );

    res.json(result.rows); // Возвращаем предметы в формате JSON
  } catch (err) {
    console.error("Ошибка при получении предметов из инвентаря:", err);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

// Маршрут для "надевания" предмета на персонажа
router.post("/equip", requireAuth, async (req, res) => {
  const { itemId, equip } = req.body;
  const userId = req.session.user.id;

  try {
    const character = await db.query(
      "SELECT id FROM rpg_characters WHERE user_id = $1",
      [userId]
    );

    if (!character.rows.length) {
      return res.status(404).json({ error: "Персонаж не найден" });
    }

    const characterId = character.rows[0].id;

    const inventoryItem = await db.query(
      "SELECT * FROM inventory WHERE character_id = $1 AND item_id = $2",
      [characterId, itemId]
    );

    if (!inventoryItem.rows.length) {
      return res.status(404).json({ error: "Предмет не найден в инвентаре" });
    }

    // Обновляем состояние предмета
    await db.query(
      "UPDATE inventory SET is_equipped = $1 WHERE character_id = $2 AND item_id = $3",
      [equip, characterId, itemId]
    );

    // Возвращаем актуальное состояние предмета
    const updatedItem = await db.query(
      "SELECT is_equipped FROM inventory WHERE character_id = $1 AND item_id = $2",
      [characterId, itemId]
    );

    res.json({
      message: equip ? "Предмет надет!" : "Предмет снят!",
      is_equipped: updatedItem.rows[0].is_equipped,
    });
  } catch (err) {
    console.error("Ошибка при изменении статуса предмета:", err);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

module.exports = router;
