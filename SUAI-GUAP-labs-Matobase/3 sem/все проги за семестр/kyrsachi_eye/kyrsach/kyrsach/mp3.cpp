#include <iostream>
#include <sqlite3.h>
#include <string>
#include <regex> // Для проверки формата года
#include <ctime> // Для работы с текущей датой и временем
#include <windows.h> // Для работы с функциями Windows API

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string year; // Изменили тип данных на std::string
    std::string genre;
};

// Функция для выполнения SQL-запросов к базе данных
int executeSQL(sqlite3* db, const std::string& query, int (*callback)(void*, int, char**, char**), void* data, char** errMsg) {
    return sqlite3_exec(db, query.c_str(), callback, data, errMsg);
}

int printCallback(void* data, int argc, char** argv, char** colNames) {
    for (int i = 0; i < argc; i++) {
        std::cout << colNames[i] << ": ";
        if (argv[i]) {
            std::cout << argv[i] << "\t";
        }
        else {
            std::cout << "NULL\t"; // Если значение в столбце NULL
        }
    }
    std::cout << "\n";
    return 0;
}

bool isValidYear(const std::string& year) {
    // Проверка формата года с использованием регулярного выражения
    std::regex yearPattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
    if (!std::regex_match(year, yearPattern)) {
        return false;
    }

    // Получение текущей даты и времени
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);

    int currentYear = sysTime.wYear;

    // Извлекаем год из строки года
    int bookYear = std::stoi(year.substr(6, 4));

    // Проверка на количество месяцев и дней в месяце
    int bookMonth = std::stoi(year.substr(3, 2));
    int bookDay = std::stoi(year.substr(0, 2));

    if (bookMonth < 1 || bookMonth > 12 || bookDay < 1 || bookDay > 31) {
        return false;
    }

    // Проверка, что год не превышает текущее время
    if (bookYear > currentYear) {
        return false;
    }

    return true;
}

int main() {
    system("chcp 1251 > nul");
    sqlite3* db;
    int rc = sqlite3_open("books.db", &db); // Открываем базу данных "books.db"

    if (rc) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // Создаем таблицу "books" для хранения информации о книгах
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "author TEXT NOT NULL,"
        "year TEXT NOT NULL,"
        "genre TEXT NOT NULL);";
    char* errMsg = 0;
    rc = executeSQL(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Сброс счетчика id
    const char* resetIdSQL = "DELETE FROM sqlite_sequence WHERE name = 'books';";
    rc = executeSQL(db, resetIdSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка сброса счетчика id: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    int choice;
    do {
        std::cout << "Выберите операцию:\n"
            << "1. Добавить книгу\n"
            << "2. Удалить книгу\n"
            << "3. Редактировать книгу\n"
            << "4. Поиск книги по названию\n"
            << "5. Поиск книги по автору\n"
            << "6. Поиск книги по жанру\n"
            << "7. Вывести все книги из базы данных\n"
            << "8. Удалить базу данных\n"
            << "0. Выйти\n"
            << "Введите число: ";
        std::cin >> choice;

        if (choice == 1) {
            Book book;
            std::cin.ignore();
            std::cout << "Введите название книги: ";
            std::getline(std::cin, book.title);
            std::cout << "Введите автора книги: ";
            std::getline(std::cin, book.author);

            // Проверка формата года и повторный ввод, если формат неверный
            do {
                std::cout << "Введите год выпуска (в формате xx.xx.xxxx): ";
                std::getline(std::cin, book.year); // Теперь считываем строку для года
                if (!isValidYear(book.year)) {
                    std::cout << "Неверный формат года. Пожалуйста, введите год в формате xx.xx.xxxx.\n";
                }
            } while (!isValidYear(book.year));

            std::cout << "Введите жанр книги: ";
            std::getline(std::cin, book.genre);

            // Выполнение SQL-запроса для добавления книги в базу данных
            std::string addBookSQL = "INSERT INTO books (title, author, year, genre) VALUES ('" +
                book.title + "', '" + book.author + "', '" + book.year + "', '" + book.genre + "');"; // Изменили тип данных года
            rc = executeSQL(db, addBookSQL, 0, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка добавления книги: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                std::cout << "Книга успешно добавлена!\n";
            }
        }
        else if (choice == 2) {
            std::cin.ignore();
            std::cout << "Введите название книги для удаления: ";
            std::string bookTitle;
            std::getline(std::cin, bookTitle);

            // Выполнение SQL-запроса для удаления книги из базы данных
            std::string deleteBookSQL = "DELETE FROM books WHERE title = '" + bookTitle + "';";
            rc = executeSQL(db, deleteBookSQL, 0, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка удаления книги: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                if (sqlite3_changes(db) == 0) {
                    std::cout << "Книги с таким названием не найдены.\n";
                }
                else {
                    std::cout << "Книга успешно удалена!\n";
                }
            }
        }
        else if (choice == 3) {
            std::cin.ignore();
            std::cout << "Введите имя автора для поиска книг: ";
            std::string authorName;
            std::getline(std::cin, authorName);

            // Выполнение SQL-запроса для поиска книг автора
            std::string searchAuthorSQL = "SELECT * FROM books WHERE author = '" + authorName + "';";
            rc = executeSQL(db, searchAuthorSQL, printCallback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка поиска книг: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                if (sqlite3_changes(db) == 0) {
                    std::cout << "Книги этого автора не найдены.\n";
                }
            }
        }
        else if (choice == 4) {
            std::cin.ignore();
            std::cout << "Введите название книги для редактирования: ";
            std::string bookTitle;
            std::getline(std::cin, bookTitle);

            // Выполнение SQL-запроса для выбора книги для редактирования
            std::string selectBookSQL = "SELECT * FROM books WHERE title = '" + bookTitle + "';";
            rc = executeSQL(db, selectBookSQL, printCallback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка выбора книги: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                Book book;
                std::cout << "Введите новое название книги: ";
                std::getline(std::cin, book.title);
                std::cout << "Введите нового автора книги: ";
                std::getline(std::cin, book.author);

                // Проверка формата года и повторный ввод, если формат неверный
                do {
                    std::cout << "Введите новый год выпуска (в формате xx.xx.xxxx): ";
                    std::getline(std::cin, book.year); // Теперь считываем строку для года
                    if (!isValidYear(book.year)) {
                        std::cout << "Неверный формат года. Пожалуйста, введите год в формате xx.xx.xxxx.\n";
                    }
                } while (!isValidYear(book.year));

                std::cout << "Введите новый жанр книги: ";
                std::getline(std::cin, book.genre);

                // Выполнение SQL-запроса для обновления информации о книге
                std::string updateBookSQL = "UPDATE books SET title = '" + book.title + "', author = '" +
                    book.author + "', year = '" + book.year + "', genre = '" + book.genre + "' WHERE title = '" + bookTitle + "';";
                rc = executeSQL(db, updateBookSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "Ошибка редактирования книги: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "Книга успешно отредактирована!\n";
                }
            }
        }
        else if (choice == 5) {
            std::cin.ignore();
            std::cout << "Введите название книги для поиска: ";
            std::string bookTitle;
            std::getline(std::cin, bookTitle);

            // Выполнение SQL-запроса для поиска книги по названию
            std::string searchTitleSQL = "SELECT * FROM books WHERE title LIKE '%" + bookTitle + "%';";
            rc = executeSQL(db, searchTitleSQL, printCallback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка поиска книг: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                if (sqlite3_changes(db) == 0) {
                    std::cout << "Книги с таким названием не найдены.\n";
                }
            }
        }
        else if (choice == 6) {
            std::cin.ignore();
            std::cout << "Введите жанр книги для поиска: ";
            std::string bookGenre;
            std::getline(std::cin, bookGenre);

            // Выполнение SQL-запроса для поиска книги по жанру
            std::string searchGenreSQL = "SELECT * FROM books WHERE genre LIKE '%" + bookGenre + "%';";
            rc = executeSQL(db, searchGenreSQL, printCallback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка поиска книг: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                if (sqlite3_changes(db) == 0) {
                    std::cout << "Книги с таким жанром не найдены.\n";
                }
            }
        }
        else if (choice == 7) {
            // Выполнение SQL-запроса для выбора всех книг из базы данных
            std::string selectAllBooksSQL = "SELECT * FROM books;";
            rc = executeSQL(db, selectAllBooksSQL, printCallback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "Ошибка вывода всех книг: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
            else {
                if (sqlite3_changes(db) == 0) {
                    std::cout << "База данных пуста.\n";
                }
            }
            }
        else if (choice == 8) {
            std::string password;
            std::cout << "Введите пароль для очистки базы данных: ";
            std::cin >> password;

            // Проверьте, что введенный пароль совпадает с вашим паролем
            if (password == "ghjcnj") { // Замените "YourPassword" на ваш реальный пароль
                const char* clearDatabaseSQL = "DELETE FROM books;"; // Очищаем таблицу
                rc = executeSQL(db, clearDatabaseSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "Ошибка очистки базы данных: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }

                // Сброс счетчика id
                const char* resetIdSQL = "DELETE FROM sqlite_sequence WHERE name = 'books';";
                rc = executeSQL(db, resetIdSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "Ошибка сброса счетчика id: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "База данных успешно очищена и счетчик id сброшен!\n";
                }
            }
            else {
                std::cout << "Неверный пароль. Очистка базы данных отменена.\n";
            }
}
        else if (choice == 0) {
            std::cout << "Программа завершена.\n";
        }
        else {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    sqlite3_close(db); // Закрываем базу данных при завершении программы
    return 0;
}