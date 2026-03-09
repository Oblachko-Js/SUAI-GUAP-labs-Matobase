//1)�������� �������� �� ������� �������� 2)���������� ����� ���� �� ������ �� �������� � � ������� �������
//3)������� ����� ���� �� ���������� ����� 4)����� � ���� ������� ������ �������� SQL
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <regex>
#include <ctime>
#include <windows.h>
#include <cctype> 
#include <locale>
#include <unicode/unistr.h>
#include <unicode/uchar.h>

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string year;
    std::string genre;
};
int choice = -1;
sqlite3* db = nullptr;
int executeSQL(const std::string& query, int (*callback)(void*, int, char**, char**), void* data = nullptr, char** errMsg = nullptr) {
    return sqlite3_exec(db, query.c_str(), callback, data, errMsg);
}

int printCallback(void* data, int argc, char** argv, char** colNames) {
    for (int i = 0; i < argc; i++) {
        std::cout << colNames[i] << ": ";
        if (argv[i]) {
            std::cout << argv[i] << "\t";
        }
        else {
            std::cout << "NULL\t";
        }
    }
    std::cout << "\n";
    return 0;
}

bool isFirstLetterCapitalAndLatin(const std::string& input) {
    if (input.empty()) {
        return false; // ������ ������ �� ����� ��������� ����
    }

    icu::UnicodeString unicodeStr = icu::UnicodeString::fromUTF8(input.c_str());

    if (unicodeStr.length() > 0) {
        UChar32 firstChar = unicodeStr.char32At(0);
        UBool isUppercase = u_isupper(firstChar); // ���������, ��� ������ ����� �������� ���������
        return static_cast<bool>(isUppercase);
    }

    return false;
}

bool isValidYear(const std::string& year) {
    // �������� ������� ���� � �������������� ����������� ���������
    std::regex yearPattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
    if (!std::regex_match(year, yearPattern)) {
        return false;
    }

    // ��������� ������� ���� � �������
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);

    int currentYear = sysTime.wYear;

    int bookYear = std::stoi(year.substr(6, 4));
    int bookMonth = std::stoi(year.substr(3, 2));
    int bookDay = std::stoi(year.substr(0, 2));

    if (bookMonth < 1 || bookMonth > 12 || bookDay < 1) {
        return false;
    }

    // �������� ����������� ���������� ���� � �������
    if (bookMonth == 2) {
        // ������� - ��������� ���������� ���
        bool isLeapYear = (bookYear % 4 == 0 && bookYear % 100 != 0) || (bookYear % 400 == 0);
        if (isLeapYear) {
            if (bookDay > 29) {
                return false;
            }
        }
        else {
            if (bookDay > 28) {
                return false;
            }
        }
    }
    else if ((bookMonth == 4 || bookMonth == 6 || bookMonth == 9 || bookMonth == 11) && bookDay > 30) {
        return false;
    }
    else if (bookDay > 31) {
        return false;
    }

    if (bookYear > currentYear) {
        return false;
    }

    return true;
}

void addBook() {
    Book book;
    std::cin.ignore();

    // �������� �� ���������� �������� �����
    do {
        std::cout << "������� �������� �����: ";
        std::getline(std::cin, book.title);

        if (!isFirstLetterCapitalAndLatin(book.title)) {
            std::cout << "������ ����� �������� ����� ������ ���� ���������. ����������, ������� �������� ����� ������.\n";
            continue;
        }

        // ��� �������� ������� ����� � ����� ���������
        std::string checkBookSQL = "SELECT COUNT(*) FROM books WHERE title = '" + book.title + "';";
        char* errMsg = nullptr;
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, checkBookSQL.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) {
                std::cout << "����� � ����� ��������� ��� ����������. ����������, ������� �������� ����� ������.\n";
            }
            else {
                break;
            }
        }

        sqlite3_finalize(stmt);
    } while (true);

    // ���� ��������� ������ � �����
    std::cout << "������� ������ �����: ";
    std::getline(std::cin, book.author);

    do {
        std::cout << "������� ��� ������� (� ������� xx.xx.xxxx): ";
        std::getline(std::cin, book.year);
        if (!isValidYear(book.year)) {
            std::cout << "�������� ������ ����. ����������, ������� ��� � ������� xx.xx.xxxx.\n";
        }
    } while (!isValidYear(book.year));

    std::cout << "������� ���� �����: ";
    std::getline(std::cin, book.genre);

    std::string addBookSQL = "INSERT INTO books (title, author, year, genre) VALUES ('" +
        book.title + "', '" + book.author + "', '" + book.year + "', '" + book.genre + "');";
    char* errMsg = nullptr;
    int rc = executeSQL(addBookSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� �����: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "����� ������� ���������!\n";
    }
}

void deleteBook() {
    std::cin.ignore();
    std::cout << "������� �������� ����� ��� ��������: ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    std::string deleteBookSQL = "DELETE FROM books WHERE title = '" + bookTitle + "';";
    char* errMsg = nullptr;
    int rc = executeSQL(deleteBookSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "������ �������� �����: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        if (sqlite3_changes(db) == 0) {
            std::cout << "����� � ����� ��������� �� �������.\n";
        }
        else {
            std::cout << "����� ������� �������!\n";
        }
    }
}

void editBook() {
    Book book;
    std::cin.ignore();
    std::cout << "������� �������� ����� ��� ��������������: ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);

    std::string selectBookSQL = "SELECT * FROM books WHERE title = '" + bookTitle + "';";
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, selectBookSQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW) {
        std::cout << "����� � ��������� '" << bookTitle << "' �� ������� � ���� ������." << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    else {
        int editChoice;
        do {
            std::cout << "��������, ��� �� ������ ���������������:\n"
                << "1. ������ �������������� �����\n"
                << "2. ������������� ������ �������� �����\n"
                << "3. ������������� ������ ������ �����\n"
                << "4. ������������� ������ ���� �����\n"
                << "5. ������������� ������ ��� ������� �����\n"
                << "0. �������� �������������� � ��������� � ������� ����\n"
                << "������� �����: ";
            std::cin >> editChoice;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "\n";
                std::cout << "������ ����� � ������ ���� ���.\n";
                std::cout << "�������� �������� ��������: ";
                std::cin >> editChoice;
            }
            switch (editChoice) {
            case 1:
            {
                std::string newBookTitle;
                bool isUnique = false;

                while (!isUnique) {
                    std::cout << "������� ����� �������� �����: ";
                    std::getline(std::cin, newBookTitle);

                    // ��������, ���������� �� ����� � ����� ��������� � ���� ������
                    std::string checkBookSQL = "SELECT * FROM books WHERE title = '" + newBookTitle + "';";
                    char* errMsg = nullptr;
                    sqlite3_stmt* checkStmt;

                    int checkRC = sqlite3_prepare_v2(db, checkBookSQL.c_str(), -1, &checkStmt, nullptr);

                    if (checkRC != SQLITE_OK) {
                        std::cerr << "������ ���������� SQL-������� ��� ��������: " << sqlite3_errmsg(db) << std::endl;
                        sqlite3_finalize(checkStmt);
                        return;
                    }

                    checkRC = sqlite3_step(checkStmt);

                    if (checkRC == SQLITE_ROW) {
                        std::cout << "����� � ��������� '" << newBookTitle << "' ��� ���������� � ���� ������. �������� ������ ��������.\n";
                        sqlite3_finalize(checkStmt);
                    }
                    else {
                        isUnique = true;
                    }
                }

                // ���� ����� �������� ���������, ���������� �������������� �����
                book.title = newBookTitle;
                std::cout << "������� ������ ������ �����: ";
                std::getline(std::cin, book.author);

                do {
                    std::cout << "������� ����� ��� ������� (� ������� xx.xx.xxxx): ";
                    std::getline(std::cin, book.year);
                    if (!isValidYear(book.year)) {
                        std::cout << "�������� ������ ����. ����������, ������� ��� � ������� xx.xx.xxxx.\n";
                    }
                } while (!isValidYear(book.year));

                std::cout << "������� ����� ���� �����: ";
                std::getline(std::cin, book.genre);

                std::string updateBookSQL = "UPDATE books SET title = '" + book.title + "', author = '" +
                    book.author + "', year = '" + book.year + "', genre = '" + book.genre + "' WHERE title = '" + bookTitle + "';";
                int rc = executeSQL(updateBookSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "������ �������������� �����: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "����� ������� ���������������!\n";
                }
            }
            break;
            case 2:
            {
                std::string newBookTitle;
                bool isUnique = false;

                while (!isUnique) {
                    std::cout << "������� ����� �������� �����: ";
                    std::getline(std::cin, newBookTitle);

                    // ��������, ���������� �� ����� � ����� ��������� � ���� ������
                    std::string checkBookSQL = "SELECT * FROM books WHERE title = '" + newBookTitle + "';";
                    char* errMsg = nullptr;
                    sqlite3_stmt* checkStmt;

                    int checkRC = sqlite3_prepare_v2(db, checkBookSQL.c_str(), -1, &checkStmt, nullptr);

                    if (checkRC != SQLITE_OK) {
                        std::cerr << "������ ���������� SQL-������� ��� ��������: " << sqlite3_errmsg(db) << std::endl;
                        sqlite3_finalize(checkStmt);
                        return;
                    }

                    checkRC = sqlite3_step(checkStmt);

                    if (checkRC == SQLITE_ROW) {
                        std::cout << "����� � ��������� '" << newBookTitle << "' ��� ���������� � ���� ������. �������� ������ ��������.\n";
                        sqlite3_finalize(checkStmt);
                    }
                    else {
                        isUnique = true;
                    }
                }

                // ���� ����� �������� ���������, ���������� �������������� �����
                std::string updateTitleSQL = "UPDATE books SET title = '" + newBookTitle + "' WHERE title = '" + bookTitle + "';";
                char* errMsg = nullptr;
                int rc = executeSQL(updateTitleSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "������ �������������� �������� �����: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "�������� ����� ������� ���������������!\n";
                }
                return;
            }
            break;
            case 3:
            {
                Book book;
                std::cout << "������� ������ ������ �����: ";
                std::getline(std::cin, book.author);

                std::string updateAuthorSQL = "UPDATE books SET author = '" + book.author + "' WHERE title = '" + bookTitle + "';";
                char* errMsg = nullptr;
                int rc = executeSQL(updateAuthorSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "������ �������������� ������ �����: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "����� ����� ������� ��������������!\n";
                }
            }
            break;
            case 4:
            {
                Book book;
                std::cout << "������� ����� ���� �����: ";
                std::getline(std::cin, book.genre);

                std::string updateGenreSQL = "UPDATE books SET genre = '" + book.genre + "' WHERE title = '" + bookTitle + "';";
                char* errMsg = nullptr;
                int rc = executeSQL(updateGenreSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "������ �������������� ����� �����: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "���� ����� ������� ��������������!\n";
                }
            }
            break;
            case 5:
            {
                Book book;
                do {
                    std::cout << "������� ����� ��� ������� (� ������� xx.xx.xxxx): ";
                    std::getline(std::cin, book.year);
                    if (!isValidYear(book.year)) {
                        std::cout << "�������� ������ ����. ����������, ������� ��� � ������� xx.xx.xxxx.\n";
                    }
                } while (!isValidYear(book.year));

                std::string updateYearSQL = "UPDATE books SET year = '" + book.year + "' WHERE title = '" + bookTitle + "';";
                char* errMsg = nullptr;
                int rc = executeSQL(updateYearSQL, 0, 0, &errMsg);

                if (rc != SQLITE_OK) {
                    std::cerr << "������ �������������� ���� ������� �����: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                }
                else {
                    std::cout << "��� ������� ����� ������� ��������������!\n";
                }
            }
            break;
            case 0:
                return;
            default:
                std::cout << "������ ����� � ������ ���� ���.\n";
                break;
            }
        } while (true);
    }
}

void searchBooksByTitle() {
    std::cin.ignore();
    std::cout << "������� �������� ����� ��� ������: ";
    std::string bookTitle;
    std::getline(std::cin, bookTitle);
    std::string searchTitleSQL = "SELECT title, author, year, genre FROM books WHERE title = '" + bookTitle + "';";
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, searchTitleSQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    bool resultsFound = false;

    int bookNumber = 1;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW) {
        std::cout << bookNumber << ") ��������: " << sqlite3_column_text(stmt, 0)
            << "\t�����: " << sqlite3_column_text(stmt, 1)
            << "\t���: " << sqlite3_column_text(stmt, 2)
            << "\t����: " << sqlite3_column_text(stmt, 3) << std::endl;
        rc = sqlite3_step(stmt);
        resultsFound = true;
        bookNumber++;
    }

    if (!resultsFound) {
        std::cout << "����� � ����� ��������� �� �������." << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void searchBooksByAuthor() {
    std::cin.ignore();
    std::cout << "������� ��� ������ ��� ������ ����: ";
    std::string authorName;
    std::getline(std::cin, authorName);
    std::string searchAuthorSQL = "SELECT title, author, year, genre FROM books WHERE author = '" + authorName + "';";
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, searchAuthorSQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    bool resultsFound = false;

    int bookNumber = 1;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW) {
        std::cout << bookNumber << ") ��������: " << sqlite3_column_text(stmt, 0)
            << "\t�����: " << sqlite3_column_text(stmt, 1)
            << "\t���: " << sqlite3_column_text(stmt, 2)
            << "\t����: " << sqlite3_column_text(stmt, 3) << "\n" << std::endl;
        rc = sqlite3_step(stmt);
        resultsFound = true;
        bookNumber++;
    }

    if (!resultsFound) {
        std::cout << "����� ����� ������ �� �������." << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void searchBooksByGenre() {
    std::cin.ignore();
    std::cout << "������� ���� ����� ��� ������: ";
    std::string bookGenre;
    std::getline(std::cin, bookGenre);
    std::string searchGenreSQL = "SELECT title, author, year, genre FROM books WHERE genre = '" + bookGenre + "';";
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, searchGenreSQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    bool resultsFound = false;

    int bookNumber = 1;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW) {
        std::cout << bookNumber << ") ��������: " << sqlite3_column_text(stmt, 0)
            << "\t�����: " << sqlite3_column_text(stmt, 1)
            << "\t���: " << sqlite3_column_text(stmt, 2)
            << "\t����: " << sqlite3_column_text(stmt, 3) << std::endl;
        rc = sqlite3_step(stmt);
        resultsFound = true;
        bookNumber++;
    }

    if (!resultsFound) {
        std::cout << "����� � ����� ������ �� �������." << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void printAllBooks() {
    std::string selectAllBooksSQL = "SELECT title, author, year, genre FROM books;";
    char* errMsg = nullptr;
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, selectAllBooksSQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    bool resultsFound = false;
    int bookNumber = 1;

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW) {
        std::cout << bookNumber << ") ��������: " << sqlite3_column_text(stmt, 0)
            << "\t�����: " << sqlite3_column_text(stmt, 1)
            << "\t���: " << sqlite3_column_text(stmt, 2)
            << "\t����: " << sqlite3_column_text(stmt, 3) << std::endl;
        rc = sqlite3_step(stmt);
        bookNumber++;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "������ ���������� SQL-�������: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    system("chcp 1251 > nul");
    // �������� ���� ������
    int rc = sqlite3_open("library.db", &db);

    if (rc) {
        std::cerr << "������ ��������/�������� ���� ������: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // �������� ������� books, ���� ��� �� ����������
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "author TEXT NOT NULL,"
        "year TEXT NOT NULL,"
        "genre TEXT NOT NULL);";
    char* errMsg = nullptr;
    rc = executeSQL(createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "������ �������� �������: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }

    do {
        std::cout << "�������� ��������:\n"
            << "1. ����� ����� �� ��������\n"
            << "2. ����� ����� �� ������\n"
            << "3. ����� ����� �� �����\n"
            << "4. �������� �����\n"
            << "5. ������������� �����\n"
            << "6. ������� �����\n"
            << "7. ������� ��� ����� �� ���� ������\n"
            << "0. �����\n"
            << "������� �����: ";

        std::cin >> choice;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\n";
            std::cout << "������ ����� � ������ ���� ���.\n";
            std::cout << "�������� �������� ��������: ";
            std::cin >> choice;
        }

        switch (choice) {
        case 1:
            std::cout << "\n";
            searchBooksByTitle();
            break;
        case 2:
            std::cout << "\n";
            searchBooksByAuthor();
            break;
        case 3:
            std::cout << "\n";
            searchBooksByGenre();
            break;
        case 4:
            std::cout << "\n";
            addBook();
            break;
        case 5:
            std::cout << "\n";
            editBook();
            break;
        case 6:
            std::cout << "\n";
            deleteBook();
            break;
        case 7:
            std::cout << "\n";
            printAllBooks();
            break;
        case 0:
            std::cout << "\n";
            std::cout << "��������� ���������.\n";
            break;
        default:
            std::cout << "\n";
            std::cout << "������ ����� � ������ ���� ���.\n";
            break;
        }
    } while (choice != 0);

    sqlite3_close(db); // ��������� ���� ������ ��� ���������� ���������
    return 0;
}
