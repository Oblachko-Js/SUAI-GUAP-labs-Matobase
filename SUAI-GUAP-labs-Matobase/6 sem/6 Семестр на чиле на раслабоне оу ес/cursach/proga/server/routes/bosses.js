const express = require("express");
const { requireAuth } = require("../middleware/authMiddleware");
const db = require("../db");
const router = express.Router();

// Маршрут для получения всех боссов (только для авторизованных пользователей)
router.get("/", requireAuth, async (req, res) => {
  try {
    const result = await db.query("SELECT * FROM bosses");
    res.status(200).json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при получении боссов" });
  }
});

// Маршрут для битвы с боссом
router.post("/:id/fight", requireAuth, async (req, res) => {
  const bossId = req.params.id;
  const userId = req.session.user.id;

  try {
    // Получаем данные о персонаже пользователя
    const characterResult = await db.query(
      "SELECT * FROM rpg_characters WHERE user_id = $1",
      [userId]
    );
    const character = characterResult.rows[0];

    if (!character) {
      return res.status(404).json({ error: "Персонаж не найден" });
    }

    // Получаем данные о боссе
    const bossResult = await db.query("SELECT * FROM bosses WHERE id = $1", [
      bossId,
    ]);
    const boss = bossResult.rows[0];

    if (!boss) {
      return res.status(404).json({ error: "Босс не найден" });
    }

    // Проверяем ману персонажа
    if (character.mana < 100) {
      return res.status(400).json({ error: "Недостаточно маны для атаки" });
    }

    // Вычисляем урон в зависимости от уровня персонажа
    const damage = 5 + (character.level - 1) * 5;
    const newBossHealth = boss.health - damage;

    // Обновляем здоровье босса
    await db.query("UPDATE bosses SET health = $1 WHERE id = $2", [
      newBossHealth,
      bossId,
    ]);

    // Обновляем ману персонажа
    await db.query(
      "UPDATE rpg_characters SET mana = mana - 100 WHERE user_id = $1",
      [userId]
    );

    // Получаем обновлённое значение маны
    const updatedCharacterResult = await db.query(
      "SELECT mana FROM rpg_characters WHERE user_id = $1",
      [userId]
    );
    const updatedMana = updatedCharacterResult.rows[0].mana;

    // Если босс побеждён
    if (newBossHealth <= 0) {
      // Выдаём награды
      await db.query(
        "UPDATE rpg_characters SET experience = experience + $1, gold = gold + $2 WHERE user_id = $3",
        [boss.reward_experience, boss.reward_gold, userId]
      );

      // Увеличиваем здоровье босса на 15 и сбрасываем его
      const newBaseHealth = boss.base_health + 15;
      await db.query(
        "UPDATE bosses SET health = $1, base_health = $1 WHERE id = $2",
        [newBaseHealth, bossId]
      );
    }

    // Возвращаем результат битвы
    res.status(200).json({
      damage,
      bossHealth: newBossHealth,
      mana: updatedMana, // Теперь updatedMana определена
      reward_experience: boss.reward_experience,
      reward_gold: boss.reward_gold,
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при сражении" });
  }
});

router.post("/restore-mana", requireAuth, async (req, res) => {
  const userId = req.session.user.id;

  try {
    // Получаем данные о персонаже пользователя
    const characterResult = await db.query(
      "SELECT * FROM rpg_characters WHERE user_id = $1",
      [userId]
    );
    const character = characterResult.rows[0];

    if (!character) {
      return res.status(404).json({ error: "Персонаж не найден" });
    }

    // Рассчитываем ману за клик
    const manaPerClick = 1 + (character.level - 1) * 0.2;

    // Преобразуем character.mana в число, если это строка
    const currentMana = parseFloat(character.mana);

    // Увеличиваем ману на значение manaPerClick и округляем до одного знака после запятой
    const newMana = parseFloat((currentMana + manaPerClick).toFixed(1));

    // Обновляем ману персонажа
    await db.query("UPDATE rpg_characters SET mana = $1 WHERE user_id = $2", [
      newMana,
      userId,
    ]);

    // Возвращаем новые значения
    res.status(200).json({
      mana: newMana,
      level: character.level,
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при восстановлении маны" });
  }
});

module.exports = router;
