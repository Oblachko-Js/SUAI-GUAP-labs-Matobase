#include <iostream>
#include <string>
#include <windows.h>

// Установка кодировки консоли на Windows-1251
void SetConsoleCP1251() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

class Book {
private:
    std::string title;
    std::string author;
    std::string publicationDate;
    char c;

public:
    // Конструктор по умолчанию
    Book();

    // Конструктор для пользовательского ввода
    Book(const std::string& title, const std::string& author, const std::string& date, char initial);

    // Конструктор копирования из данных вводимых пользователем
    Book(const Book& other);

    // Деструктор
    ~Book();

    // Метод для установки данных книги
    void setData(const std::string& title, const std::string& author, const std::string& date);

    // Метод для получения названия книги
    std::string getTitle() const;

    // Метод для получения имени автора
    std::string getAuthor() const;

    // Метод для установки начальной буквы
    void setAuthorInitial(char initial);

    // Метод для проверки начальной буквы автора книги
    void checkAuthorInitial(const std::string& bookName);
};

// Конструктор по умолчанию
Book::Book() : title("Балка"), author("Антон"), publicationDate("20.07.2007"), c('С') {
    std::cout << "Вызван конструктор по умолчанию" << std::endl;
    std::cout << "Название: " << title << ", Автор: " << author << ", Дата издания: " << publicationDate << std::endl;
}

// Конструктор для пользовательского ввода
Book::Book(const std::string& title, const std::string& author, const std::string& date, char initial)
    : title(title), author(author), publicationDate(date), c(initial) {
    std::cout << "Вызван конструктор с параметрами" << std::endl;
    std::cout << "Название: " << title << ", Автор: " << author << ", Дата издания: " << publicationDate << std::endl;
}

// Конструктор копирования из данных вводимых пользователем
Book::Book(const Book& other)
    : title(other.title), author(other.author), publicationDate(other.publicationDate), c(other.c) {
    std::cout << "Вызван конструктор копирования" << std::endl;
    std::cout << "Название: " << title << ", Автор: " << author << ", Дата издания: " << publicationDate << std::endl;
}

// Деструктор
Book::~Book() {}

// Метод для установки данных книги
void Book::setData(const std::string& title, const std::string& author, const std::string& date) {
    this->title = title;
    this->author = author;
    this->publicationDate = date;
}

// Метод для получения названия книги
std::string Book::getTitle() const {
    return title;
}

// Метод для получения имени автора
std::string Book::getAuthor() const {
    return author;
}

// Метод для установки начальной буквы
void Book::setAuthorInitial(char initial) {
    c = initial;
}

// Метод для проверки начальной буквы автора книги
void Book::checkAuthorInitial(const std::string& bookName) {
    if (!std::isspace(static_cast<unsigned char>(c))) {
        if (author.empty()) {
            std::cout << "Автор " << bookName << " не начинается с буквы '" << c << "'" << std::endl;
        }
        else if (author[0] == c) {
            std::cout << "Автор " << bookName << " начинается с буквы '" << c << "'" << std::endl;
        }
        else {
            std::cout << "Автор " << bookName << " не начинается с буквы '" << c << "'" << std::endl;
        }
    }
}

int main() {
    // Установка кодировки консоли на Windows-1251
    SetConsoleCP1251();
    system("color 71");
    // Получение данных от пользователя
    std::string title, author, date;
    char c, c2, c3; // Добавлены дополнительные переменные для букв
    std::cout << "Введите название книги: ";
    std::getline(std::cin, title);
    // Проверка на пустой ввод
    if (title.empty()) {
        std::cout << "Название книги не может быть пустым." << std::endl;
        return 1;
    }
    std::cout << "Введите имя автора: ";
    std::getline(std::cin, author);
    // Проверка на пустой ввод
    if (author.empty()) {
        std::cout << "Имя автора не может быть пустым." << std::endl;
        return 1;
    }
    std::cout << "Введите дату издания: ";
    std::getline(std::cin, date);
    // Проверка на пустой ввод
    if (date.empty()) {
        std::cout << "Дата издания не может быть пустой." << std::endl;
        return 1;
    }
    std::cout << "Введите букву для конструктора с параметрами: ";
    std::cin >> c;
    std::cout << "Введите букву для конструктора копирования: ";
    std::cin >> c3;

    // Создание объекта с использованием конструктора с параметрами
    Book book1(title, author, date, c);

    // Создание объекта с использованием конструктора по умолчанию (теперь с определенными значениями)
    Book book2;

    // Создание объекта с использованием конструктора копирования
    Book book3 = book1;
    book3.setData(title, author, date); // Установка данных для третьей книги
    book3.setAuthorInitial(c3); // Установка начальной буквы для третьей книги

    // Проверка автора для каждой книги, вызывая метод checkAuthorInitial
    book1.checkAuthorInitial("книги 1");
    book2.checkAuthorInitial("книги 2");
    book3.checkAuthorInitial("книги 3");

    return 0;
}
