const bcrypt = require("bcryptjs");
const express = require("express");
const db = require("../db");
const router = express.Router();

//Для создания пользователя admin
/* const createAdminUser = async () => {
  try {
    // Проверяем, существует ли уже администратор
    const adminCheck = await db.query("SELECT * FROM users WHERE login = $1", [
      "admin",
    ]);

    // Если администратора нет, добавляем его
    if (adminCheck.rows.length === 0) {
      const hashedPassword = await bcrypt.hash("admin", 10); // Хэшируем пароль
      await db.query(
        "INSERT INTO users (login, email, password, state) VALUES ($1, $2, $3, $4)",
        ["admin", "admin", hashedPassword, "Активна"]
      );
      console.log("Администратор успешно добавлен в базу данных.");
    } else {
      console.log("Администратор уже существует.");
    }
  } catch (err) {
    console.error("Ошибка при добавлении администратора:", err);
  }
};

// Вызов функции при запуске сервера
createAdminUser(); */

// Регистрация пользователя
router.post("/register", async (req, res) => {
  const { login, email, password } = req.body;

  try {
    // Проверяем, существует ли уже пользователь с таким логином или email
    const existingUser = await db.query(
      "SELECT * FROM users WHERE login = $1 OR email = $2",
      [login, email]
    );

    if (existingUser.rows.length > 0) {
      return res
        .status(400)
        .json({ error: "Такой логин или email уже существует" });
    }

    // Хешируем пароль
    const hashedPassword = await bcrypt.hash(password, 10);

    // Добавляем нового пользователя в базу
    const result = await db.query(
      "INSERT INTO users (login, email, password) VALUES ($1, $2, $3) RETURNING *",
      [login, email, hashedPassword]
    );

    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при регистрации" });
  }
});

// Логин пользователя
router.post("/login", async (req, res) => {
  const { email, password } = req.body;
  try {
    let result;

    if (email === "admin") {
      result = await db.query("SELECT * FROM users WHERE login = $1", [
        "admin",
      ]);
    } else {
      result = await db.query("SELECT * FROM users WHERE email = $1", [email]);
    }

    if (result.rows.length > 0) {
      const user = result.rows[0];
      const passwordMatch = await bcrypt.compare(password, user.password);
      if (passwordMatch) {
        req.session.user = user;
        await db.query("UPDATE users SET last_active = NOW() WHERE id = $1", [
          user.id,
        ]);

        if (user.login === "admin") {
          res
            .status(200)
            .json({ message: "Успешный вход", user, isAdmin: true });
        } else {
          res
            .status(200)
            .json({ message: "Успешный вход", user, isAdmin: false });
        }
      } else {
        res.status(401).json({ error: "Неверный пароль" });
      }
    } else {
      res.status(401).json({ error: "Пользователь не найден" });
    }
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "Ошибка при входе" });
  }
});

// Проверка авторизации
router.get("/check", (req, res) => {
  if (req.session.user) {
    res.status(200).json({ user: req.session.user });
  } else {
    res.status(401).json({ error: "Не авторизован" });
  }
});

module.exports = router;
