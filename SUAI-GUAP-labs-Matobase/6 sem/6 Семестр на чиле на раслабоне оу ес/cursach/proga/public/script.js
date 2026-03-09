document
  .getElementById("registerForm")
  .addEventListener("submit", async (e) => {
    e.preventDefault();
    const login = document.getElementById("registerLogin").value;
    const email = document.getElementById("registerEmail").value;
    const password = document.getElementById("registerPassword").value;

    try {
      const response = await fetch("http://localhost:3000/auth/register", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ login, email, password }),
      });

      const data = await response.json();

      if (response.ok) {
        showMessage("✅ Регистрация успешна!", "success");
      } else {
        showMessage(
          `❌ Ошибка: ${data.error || "Неизвестная ошибка"}`,
          "error"
        );
      }
    } catch (error) {
      showMessage("❌ Ошибка соединения с сервером", "error");
      console.error("Ошибка при отправке запроса:", error);
    }
  });

document.getElementById("loginForm").addEventListener("submit", async (e) => {
  e.preventDefault();
  const emailOrLogin = document.getElementById("loginEmail").value; // Поле может содержать email или логин
  const password = document.getElementById("loginPassword").value;

  const response = await fetch("http://localhost:3000/auth/login", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ email: emailOrLogin, password }), // Передаем значение как email
  });

  const data = await response.json();
  if (response.ok) {
    showMessage("Вход выполнен успешно!");
    // Перенаправление на страницу в зависимости от роли
    if (data.isAdmin) {
      window.location.href = "/admin.html";
    } else {
      window.location.href = "/user.html";
    }
  } else {
    showMessage(data.error || "Ошибка при входе");
  }
});

function showMessage(message, type) {
  const messageDiv = document.getElementById("message");
  messageDiv.textContent = message;
  messageDiv.className = type; // Добавляем класс для стилизации
  setTimeout(() => {
    messageDiv.textContent = "";
    messageDiv.className = ""; // Убираем класс после исчезновения
  }, 3000);
}
