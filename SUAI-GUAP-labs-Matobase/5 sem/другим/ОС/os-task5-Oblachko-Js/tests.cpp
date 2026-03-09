#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

// Функция для проверки логина и пароля
bool validate_credentials(const std::string& username, const std::string& password) {
    const std::string valid_username = "user"; // Замените на ваш логин
    const std::string valid_password = "password"; // Замените на ваш пароль
    return (username == valid_username && password == valid_password);
}

// Функция для проверки блокировки
bool is_blocked(int failed_attempts, int max_attempts) {
    return failed_attempts >= max_attempts;
}

int main() {
    // Тестирование правильных учетных данных
    assert(validate_credentials("user", "password") == true);
    
    // Тестирование неправильных учетных данных
    assert(validate_credentials("user", "wrong_password") == false);
    assert(validate_credentials("wrong_user", "password") == false);
    
    // Тестирование логики блокировки
    int max_attempts = 3;
    int attempts = 0;

    // Проверка, что при 2 неудачных попытках клиент не заблокирован
    attempts = 2;
    assert(is_blocked(attempts, max_attempts) == false);

    // Проверка, что при 3 неудачных попытках клиент заблокирован
    attempts = 3;
    assert(is_blocked(attempts, max_attempts) == true);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
