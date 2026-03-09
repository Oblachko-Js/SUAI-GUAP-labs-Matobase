#include <iostream>
#include <string>
#include <cassert>

// Заглушка для проверки учетных данных
bool mock_validate_credentials(const std::string& username, const std::string& password) {
    // Предположим, что правильные учетные данные: "user" и "password"
    return (username == "user" && password == "password");
}

// Заглушка для проверки блокировки
bool mock_is_blocked(int failed_attempts, int max_attempts) {
    return failed_attempts >= max_attempts;
}

int main() {
    // Тестирование правильных учетных данных
    assert(mock_validate_credentials("user", "password") == true);
    
    // Тестирование неправильных учетных данных
    assert(mock_validate_credentials("user", "wrong_password") == false);
    assert(mock_validate_credentials("wrong_user", "password") == false);
    
    // Тестирование логики блокировки
    int max_attempts = 3;
    
    // Проверка, что при 2 неудачных попытках клиент не заблокирован
    assert(mock_is_blocked(2, max_attempts) == false);

    // Проверка, что при 3 неудачных попытках клиент заблокирован
    assert(mock_is_blocked(3, max_attempts) == true);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
