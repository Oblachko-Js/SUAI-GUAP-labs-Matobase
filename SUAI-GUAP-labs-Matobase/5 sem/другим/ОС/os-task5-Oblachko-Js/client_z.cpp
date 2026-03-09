#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

// Заглушка для отправки данных на сервер
void mock_send(const std::string& data) {
    std::cout << "Sending data to server: " << data << std::endl;
}

// Заглушка для получения ответа от сервера
std::string mock_receive() {
    return "Server response: Invalid credentials. Attempts left: 2"; // Имитация ответа от сервера
}

int main() {
    // Имитация ввода логина и пароля
    std::string username = "user";
    std::string password = "wrong_password";

    // Отправляем данные на сервер
    mock_send(username + " " + password);

    // Получаем ответ от сервера
    std::string response = mock_receive();
    
    // Проверяем ответ
    assert(response == "Server response: Invalid credentials. Attempts left: 2");

    std::cout << response << std::endl;

    return 0;
}
