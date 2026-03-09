const express = require("express");
const session = require("express-session");
const bodyParser = require("body-parser");
const cors = require("cors");
const db = require("./db");
const authRoutes = require("./routes/auth");
const adminRoutes = require("./routes/admin");
const userRoutes = require("./routes/user");
const tasksRoutes = require("./routes/tasks");
const habitsRoutes = require("./routes/habits");
const bossesRoutes = require("./routes/bosses");
const itemsRoutes = require("./routes/items");
const inventoryRoutes = require("./routes/inventory");
const path = require("path");

const app = express();
const port = 3000;

// Настройка сессий
app.use(
  session({
    secret: "key", // Секретный ключ для подписи сессии
    resave: false,
    saveUninitialized: true,
    cookie: { secure: false }, // Для HTTPS установить true
  })
);

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Подключение к базе данных
db.connect();

// Маршруты
app.use("/auth", authRoutes);
app.use("/admin", adminRoutes);
app.use("/user", userRoutes);
app.use("/tasks", tasksRoutes);
app.use("/habits", habitsRoutes);
app.use("/bosses", bossesRoutes);
app.use("/api", itemsRoutes);
app.use("/api", inventoryRoutes);

// Раздаём статические файлы (CSS, JS, картинки) + открытый доступ к index.html
app.use(express.static(path.join(__dirname, "../public")));

// Защищённый доступ к user.html
app.get("/user.html", (req, res) => {
  if (!req.session.user) {
    return res.redirect("/"); // Перенаправляем на index.html
  }
  res.sendFile(path.join(__dirname, "../public/user.html"));
});

// Защищённый доступ к admin.html
app.get("/admin.html", (req, res) => {
  if (req.session.user && req.session.user.login === "admin") {
    res.sendFile(path.join(__dirname, "../public/admin.html"));
  } else {
    res.status(403).send("Доступ запрещён");
  }
});

// Защищённый доступ к bosses.html
app.get("/bosses.html", (req, res) => {
  if (!req.session.user) {
    return res.redirect("/"); // Перенаправляем на index.html, если пользователь не авторизован
  }
  res.sendFile(path.join(__dirname, "../public/bosses.html"));
});

// Запуск сервера
app.listen(port, () => {
  console.log(`Сервер запущен на http://localhost:${port}`);
});
