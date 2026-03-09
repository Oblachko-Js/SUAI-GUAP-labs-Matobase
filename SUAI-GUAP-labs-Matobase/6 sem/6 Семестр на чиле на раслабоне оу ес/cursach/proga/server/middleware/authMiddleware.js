function requireAuth(req, res, next) {
  if (req.session.user) {
    next(); // Пользователь авторизован, продолжаем
  } else {
    res.status(401).json({ error: "Не авторизован" });
  }
}

function requireAdmin(req, res, next) {
  if (req.session.user && req.session.user.login === "admin") {
    next();
  } else {
    res.status(403).json({ error: "Доступ запрещен" });
  }
}

module.exports = { requireAuth, requireAdmin };
