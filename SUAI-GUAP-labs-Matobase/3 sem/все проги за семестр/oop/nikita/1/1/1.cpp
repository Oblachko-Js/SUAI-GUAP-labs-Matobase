//3 лаба
#include <iostream>
#include <algorithm>
#include <limits> // Для очистки ввода от ошибок

class Rectangle {
private:
    double width;
    double height;

public:
    // Конструктор для установки начальных значений полей
    Rectangle(double w = 0.0, double h = 0.0) : width(w), height(h) {}

    // Перегруженный оператор для вычисления площади (метод класса)
    double operator()() const;

    // Перегруженный оператор для пересечения прямоугольников (метод класса)
    Rectangle operator*(const Rectangle& other) const;
};

// Перегруженный оператор для вычисления площади (метод класса)
double Rectangle::operator()() const {
    return width * height;
}

// Перегруженный оператор для пересечения прямоугольников (метод класса)
Rectangle Rectangle::operator*(const Rectangle& other) const {
    double newWidth = std::min(width, other.width);
    double newHeight = std::min(height, other.height);
    return Rectangle(newWidth, newHeight);
}

// Дружественная функция для перегрузки оператора сравнения (по площади)
bool operator<(const Rectangle& rect1, const Rectangle& rect2);

// Функция для безопасного ввода положительных чисел типа double
double safeInputDouble();

// Дружественная функция для перегрузки оператора сравнения (по площади)
bool operator<(const Rectangle& rect1, const Rectangle& rect2) {
    return rect1() < rect2();
}

// Функция для безопасного ввода положительных чисел типа double
double safeInputDouble() {
    double value;
    while (true) {
        if (!(std::cin >> value) || value <= 0.0) {
            std::cin.clear(); // Очистка ошибок ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cout << "Некорректный ввод. Введите положительное число: ";
        }
        else {
            break;
        }
    }
    return value;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    // Введите значения для первого прямоугольника
    std::cout << "Введите ширину первого прямоугольника: ";
    double width1 = safeInputDouble();
    std::cout << "Введите высоту первого прямоугольника: ";
    double height1 = safeInputDouble();

    Rectangle rect1(width1, height1);

    // Введите значения для второго прямоугольника
    std::cout << "Введите ширину второго прямоугольника: ";
    double width2 = safeInputDouble();
    std::cout << "Введите высоту второго прямоугольника: ";
    double height2 = safeInputDouble();

    Rectangle rect2(width2, height2);

    // Пересечение прямоугольников с использованием метода класса
    Rectangle intersection = rect1 * rect2;
    std::cout << "Площадь пересечения: " << intersection() << std::endl;

    // Сравнение прямоугольников по площади с использованием дружественной функции
    if (rect1 < rect2) {
        std::cout << "Прямоугольник1 < Прямоугольник2 по площади" << std::endl;
    }
    else {
        std::cout << "Прямоугольник1 >= Прямоугольник2 по площади" << std::endl;
    }

    return 0;
}
