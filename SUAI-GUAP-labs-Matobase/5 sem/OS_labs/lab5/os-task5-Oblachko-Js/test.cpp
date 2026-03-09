#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>

// Функция проверки на простоту
bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

// Функция для проверки аргументов командной строки
void check_arguments(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Error: Incorrect number of arguments. Expected 1 argument.");
    }

    int number = std::stoi(argv[1]);
    if (number < 0 || number > 100) {
        throw std::out_of_range("Error: Argument out of range (0-100).");
    }
}

// Основная функция для запуска тестов.
int main(int argc, char* argv[]) {
    // Тесты на простоту
    assert(is_prime(2) == true);
    assert(is_prime(3) == true);
    assert(is_prime(4) == false);
    assert(is_prime(5) == true);
    assert(is_prime(9) == false);
    assert(is_prime(11) == true);
    
    // Тесты для проверки аргументов
    try {
        char* argv1[] = { "program_name", "arg1", "arg2" }; // Неправильное количество аргументов
        check_arguments(3, argv1);
        assert(false); // Если функция не выбросила исключение, тест провален
    } catch (const std::invalid_argument& e) {
        std::cout << "Test passed: " << e.what() << std::endl;
    }

    try {
        char* argv2[] = { "program_name", "-5" }; // Неправильное значение
        check_arguments(2, argv2);
        assert(false); // Если функция не выбросила исключение, тест провален
    } catch (const std::out_of_range& e) {
        std::cout << "Test passed: " << e.what() << std::endl;
    }

    try {
        char* argv3[] = { "program_name", "150" }; // Неправильное значение
        check_arguments(2, argv3);
        assert(false); // Если функция не выбросила исключение, тест провален
    } catch (const std::out_of_range& e) {
        std::cout << "Test passed: " << e.what() << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}
