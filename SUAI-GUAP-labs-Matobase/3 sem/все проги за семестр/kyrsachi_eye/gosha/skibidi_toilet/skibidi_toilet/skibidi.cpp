#include <iostream>
#include <sqlite3.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cstring>
#include <algorithm>  
#include <cctype>

using namespace std;

struct Product {
    int id;
    char name[50];
    char shop_name[50];
    float cost;
};

enum class SortType { NAME, SHOP_NAME, COST };

void printHeader() {
    cout << left << setw(5) << "№" << setw(30) << "Название товара" << setw(20) << "Магазин" << setw(10) << "Цена" << endl;
}

void printProduct(const Product& product) {
    cout << left << setw(5) << product.id << setw(30) << product.name << setw(20) << product.shop_name << setw(10) << product.cost << endl;
}

// Функция для сравнения строк без учета регистра
bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
        [](char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
        });
}

// Функция для преобразования строки в нижний регистр
std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool isProductUnique(sqlite3* db, const Product& product) {
    const char* selectSQL = "SELECT * FROM products WHERE LOWER(name) = LOWER(?) AND LOWER(shop_name) = LOWER(?) AND cost <= ?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, product.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product.shop_name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product.cost);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);

    const char* selectHigherCostSQL = "SELECT * FROM products WHERE LOWER(name) = LOWER(?) AND LOWER(shop_name) = LOWER(?) AND cost > ?;";

    rc = sqlite3_prepare_v2(db, selectHigherCostSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, product.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product.shop_name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product.cost);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

sqlite3* createDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("products.db", &db);
    if (rc) {
        cerr << "Ошибка при открытии/создании базы данных: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }
    return db;
}

void createProductTable(sqlite3* db) {
    const char* createTableSQL =
        "CREATE TABLE IF NOT EXISTS products (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "name TEXT NOT NULL COLLATE NOCASE," \
        "shop_name TEXT NOT NULL COLLATE NOCASE," \
        "cost REAL NOT NULL," \
        "UNIQUE(name, shop_name, cost) ON CONFLICT REPLACE);";

    int rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc) {
        cerr << "Ошибка при создании таблицы: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }
}

void addNewProduct(sqlite3* db, const Product& product) {
    const char* insertSQL = "INSERT INTO products (name, shop_name, cost) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, product.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, product.shop_name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, product.cost);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_finalize(stmt);
}

vector<Product> findProducts(sqlite3* db, const string& filter) {
    vector<Product> products;
    const char* selectSQL = "SELECT * FROM products WHERE LOWER(name) = ? OR shop_name = ? OR cost = ?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    const char* filterCStr = filter.c_str();
    sqlite3_bind_text(stmt, 1, filterCStr, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, filterCStr, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, atof(filterCStr));

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Product product;
        product.id = products.size() + 1; // Используйте размер вектора для порядкового номера
        strcpy_s(product.name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        strcpy_s(product.shop_name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        product.cost = static_cast<float>(sqlite3_column_double(stmt, 3));

        products.push_back(product);
    }

    sqlite3_finalize(stmt);

    return products;
}

bool doesProductExist(sqlite3* db, const char* productName, const char* shopName) {
    const char* selectSQL = "SELECT * FROM products WHERE name = ? AND shop_name = ?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, productName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, shopName, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    bool exists = rc == SQLITE_ROW;

    sqlite3_finalize(stmt);

    return exists;
}

void editProduct(sqlite3* db, const char* productName, const char* shopName, const Product& updatedProduct) {
    const char* updateSQL = "UPDATE products SET name = ?, shop_name = ?, cost = ? WHERE name = ? AND shop_name = ?;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, updateSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, updatedProduct.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, updatedProduct.shop_name, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, updatedProduct.cost);
    sqlite3_bind_text(stmt, 4, productName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, shopName, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Ошибка при выполнении запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_finalize(stmt);
}

void deleteProduct(sqlite3* db, const char* productName, const char* shopName) {
    const char* deleteSQL = "DELETE FROM products WHERE LOWER(name) = LOWER(?) AND LOWER(shop_name) = LOWER(?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, productName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, shopName, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (sqlite3_changes(db) > 0) {
        cout << "Товар успешно удален." << endl;
    }
    else {
        cout << "Товар не найден и не удален." << endl;
    }

    sqlite3_finalize(stmt);
}

bool compareByName(const Product& a, const Product& b) {
    return strcmp(a.name, b.name) < 0;
}

bool compareByShopName(const Product& a, const Product& b) {
    return strcmp(a.shop_name, b.shop_name) < 0;
}

bool compareByCost(const Product& a, const Product& b) {
    return a.cost < b.cost;
}

void listProductsSorted(sqlite3* db, SortType sortType) {
    const char* selectAllSQL = "SELECT * FROM products;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectAllSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    vector<Product> productsList;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Product product;
        strcpy_s(product.name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        strcpy_s(product.shop_name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        product.cost = static_cast<float>(sqlite3_column_double(stmt, 3));
        productsList.push_back(product);
    }

    sqlite3_finalize(stmt);

    switch (sortType) {
    case SortType::NAME:
        sort(productsList.begin(), productsList.end(), compareByName);
        break;
    case SortType::SHOP_NAME:
        sort(productsList.begin(), productsList.end(), compareByShopName);
        break;
    case SortType::COST:
        sort(productsList.begin(), productsList.end(), compareByCost);
        break;
    default:
        cout << "Неверный выбор сортировки." << endl;
        return;
    }

    printHeader();

    int Number = 1; 

    for (const Product& product : productsList) {
        cout << std::setw(5) << std::left << Number
            << std::setw(30) << product.name
            << std::setw(20) << product.shop_name
            << std::setw(10) << product.cost << endl;
        Number++; 
    }
}

void listAllProducts(sqlite3* db) {
    const char* selectAllSQL = "SELECT * FROM products;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectAllSQL, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
        exit(1);
    }

    printHeader();

    int Number = 1; // Счетчик порядкового номера

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Product product;
        strcpy_s(product.name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        strcpy_s(product.shop_name, reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        product.cost = static_cast<float>(sqlite3_column_double(stmt, 3));

        // Заменяем вывод ID на порядковый номер
        cout << std::setw(5) << std::left << Number
            << std::setw(30) << product.name
            << std::setw(20) << product.shop_name
            << std::setw(10) << product.cost << endl;

        Number++; // Увеличиваем счетчик порядкового номера
    }

    sqlite3_finalize(stmt);
}

int main() {
    int choice = 0;
    int searchChoice = 0;
    int sortChoice = 0;
    system("chcp 1251 > nul");
    sqlite3* db = createDatabase();
    createProductTable(db);

    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Найти товар" << endl;
        cout << "3. Редактировать товар" << endl;
        cout << "4. Удалить товар" << endl;
        cout << "5. Вывести список товаров" << endl;
        cout << "6. Вывести все товары и магазины" << endl;
        cout << "7. Выйти из программы" << endl;
        cout << "Введите число: ";
        cin >> choice;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Такого числа в пункте меню нет.\n";
            cout << "Введите повторно: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: {
            Product newProduct;
            cout << "Введите название товара: ";
            cin.ignore();
            cin.getline(newProduct.name, sizeof(newProduct.name));
            cout << "Введите название магазина: ";
            cin.getline(newProduct.shop_name, sizeof(newProduct.shop_name));
            cout << "Введите стоимость товара: ";
            cin >> newProduct.cost;
            while (cin.fail() || newProduct.cost <= 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Цена должна быть числом и не меньше единицы.\n";
                cout << "Введите повторно: ";
                cin >> newProduct.cost;
            }

            if (strlen(newProduct.name) == 0 || strlen(newProduct.shop_name) == 0 || newProduct.cost <= 0) {
                cout << "Неверные данные товара." << endl;
            }
            else if (!isProductUnique(db, newProduct)) {
                cout << "Такой товар уже есть." << endl;
            }
            else {
                addNewProduct(db, newProduct);
                cout << "Товар добавлен." << endl;
            }
            break;
        }
        case 2: {
            while (true) {
                cout << "Выберите параметр поиска:" << endl;
                cout << "1. По названию" << endl;
                cout << "2. По магазину" << endl;
                cout << "3. По цене" << endl;
                cout << "4. Вернуться в главное меню" << endl;
                cout << "Введите число: ";
                cin >> searchChoice;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Такого числа в пункте меню нет.\n";
                    cout << "Введите повторно: ";
                    cin >> searchChoice;
                }
                if (searchChoice == 4) {
                    break;
                }

                cin.ignore();
                cout << "Введите фильтр для поиска: ";
                string filter;
                getline(cin, filter);

                vector<Product> foundProducts;

                switch (searchChoice) {
                case 1:
                    foundProducts = findProducts(db, filter);
                    break;
                case 2: {
                    string filterLowerCase = toLowerCase(filter);

                    const char* selectShopNameSQL = "SELECT DISTINCT name, cost FROM products WHERE LOWER(shop_name) = ?;";
                    sqlite3_stmt* shopNameStmt;
                    int rc = sqlite3_prepare_v2(db, selectShopNameSQL, -1, &shopNameStmt, 0);

                    if (rc != SQLITE_OK) {
                        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
                        exit(1);
                    }

                    const char* filterCStr = filterLowerCase.c_str();
                    sqlite3_bind_text(shopNameStmt, 1, filterCStr, -1, SQLITE_STATIC);

                    while ((rc = sqlite3_step(shopNameStmt)) == SQLITE_ROW) {
                        const char* shopName = reinterpret_cast<const char*>(sqlite3_column_text(shopNameStmt, 0));
                        cout << "Магазин: " << shopName << endl;

                        const char* selectProductsSQL = "SELECT name, cost FROM products WHERE LOWER(shop_name) = ?;";
                        sqlite3_stmt* productsStmt;
                        rc = sqlite3_prepare_v2(db, selectProductsSQL, -1, &productsStmt, 0);

                        if (rc != SQLITE_OK) {
                            cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
                            exit(1);
                        }

                        sqlite3_bind_text(productsStmt, 1, filterCStr, -1, SQLITE_STATIC);

                        while ((rc = sqlite3_step(productsStmt)) == SQLITE_ROW) {
                            Product product;
                            product.id = foundProducts.size() + 1; 
                            strcpy_s(product.name, reinterpret_cast<const char*>(sqlite3_column_text(productsStmt, 0)));
                            strcpy_s(product.shop_name, shopName);
                            product.cost = static_cast<float>(sqlite3_column_double(productsStmt, 1));
                            foundProducts.push_back(product);
                        }

                        sqlite3_finalize(productsStmt);
                    }

                    sqlite3_finalize(shopNameStmt);
                    break;
                }
                case 3: {
                    float price = atof(filter.c_str());
                    const char* selectPriceSQL = "SELECT name, shop_name, cost FROM products WHERE cost = ?;";
                    sqlite3_stmt* priceStmt;
                    int rc = sqlite3_prepare_v2(db, selectPriceSQL, -1, &priceStmt, 0);

                    if (rc != SQLITE_OK) {
                        cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << endl;
                        exit(1);
                    }

                    sqlite3_bind_double(priceStmt, 1, price);

                    while ((rc = sqlite3_step(priceStmt)) == SQLITE_ROW) {
                        Product product;
                        product.id = foundProducts.size() + 1; // Используйте размер вектора для порядкового номера
                        strcpy_s(product.name, reinterpret_cast<const char*>(sqlite3_column_text(priceStmt, 0)));
                        strcpy_s(product.shop_name, reinterpret_cast<const char*>(sqlite3_column_text(priceStmt, 1)));
                        product.cost = static_cast<float>(sqlite3_column_double(priceStmt, 2));
                        foundProducts.push_back(product);
                    }

                    sqlite3_finalize(priceStmt);
                    break;
                }
                default:
                    cout << "Неверный выбор." << endl;
                    break;
                }

                if (!foundProducts.empty()) {
                    cout << "Найденные товары:" << endl;
                    printHeader();
                    int Number = 1;
                    for (const Product& product : foundProducts) {
                        printProduct(product);
                        Number++;
                    }
                }
                else {
                    cout << "Товары не найдены." << endl;
                }
            }
            break;
        }
        case 3: {
            char productName[50];
            char shopName[50];
            cout << "Введите название товара для редактирования: ";
            cin.ignore();
            cin.getline(productName, sizeof(productName));

            cout << "Введите название магазина для редактирования: ";
            cin.getline(shopName, sizeof(shopName));

            // Преобразование введенных названий товара и магазина в нижний регистр
            std::string productNameLower = toLowerCase(productName);
            std::string shopNameLower = toLowerCase(shopName);

            if (!doesProductExist(db, productNameLower.c_str(), shopNameLower.c_str())) {
                cout << "Такого товара и магазина нет в базе данных." << endl;
                break;
            }

            Product updatedProduct;
            cout << "Введите новое название товара: ";
            cin.getline(updatedProduct.name, sizeof(updatedProduct.name));
            cout << "Введите новое название магазина: ";
            cin.getline(updatedProduct.shop_name, sizeof(updatedProduct.shop_name));

            // Преобразование введенных новых названий товара и магазина в нижний регистр
            std::string updatedProductNameLower = toLowerCase(updatedProduct.name);
            std::string updatedShopNameLower = toLowerCase(updatedProduct.shop_name);

            // Проверяем, существует ли товар с таким новым названием в этом магазине
            if (doesProductExist(db, updatedProductNameLower.c_str(), updatedShopNameLower.c_str())) {
                cout << "Такой товар уже существует в данном магазине. Редактирование невозможно." << endl;
            }
            else {
                cout << "Введите новую стоимость товара: ";
                cin >> updatedProduct.cost;
                while (cin.fail() || updatedProduct.cost <= 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Цена должна быть числом и больше нуля.\n";
                    cout << "Введите повторно: ";
                    cin >> updatedProduct.cost;
                }
                editProduct(db, productNameLower.c_str(), shopNameLower.c_str(), updatedProduct);
                cout << "Товар успешно отредактирован." << endl;
            }
            break;
        }
        case 4: {
            char productName[50];
            char shopName[50];
            cout << "Введите название товара: ";
            cin.ignore();
            cin.getline(productName, sizeof(productName));
            cout << "Введите название магазина: ";
            cin.getline(shopName, sizeof(shopName));

            deleteProduct(db, productName, shopName);
            break;
        }
        case 5: {
            cout << "Выберите параметр сортировки:" << endl;
            cout << "1. По названию" << endl;
            cout << "2. По названию магазина" << endl;
            cout << "3. По стоимости" << endl;
            cout << "4. Выйти в главное меню" << endl;
            cout << "Введите число: ";
            cin >> sortChoice;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Такого числа в пункте меню нет.\n";
                cout << "Введите повторно: ";
                cin >> sortChoice;
            }

            if (sortChoice == 4)
                break;

            SortType sortType;

            switch (sortChoice) {
            case 1:
                sortType = SortType::NAME;
                break;
            case 2:
                sortType = SortType::SHOP_NAME;
                break;
            case 3:
                sortType = SortType::COST;
                break;
            default:
                cout << "Неверный выбор сортировки." << endl;
                break;
            }

            listProductsSorted(db, sortType);
            break;
        }
        case 6: {
            listAllProducts(db);
            break;
        }
        case 7: {
            sqlite3_close(db);
            return 0;
        }
        default: {
            cout << "Такого числа в пункте меню нет." << endl;
            break;
        }
        }
    }
}