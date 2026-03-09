#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <regex>

using namespace std;

const int n = 2500; // изменено количество сегментов хеш-таблицы
const int m = 6;    // длина ключа
const int m1 = 7;   // длина ключа + 1
const int tour = 11; // кол-во итераций поиска
const int c = 1;    // шаг при разрешении коллизии

struct KeyValuePair {
    char key[m1];
    char value[50]; // Измените размер по вашему усмотрению
    bool isDeleted;  // Флаг, указывающий на удаление
};
// Функция хеширования
int Hash(const char key[m1]) {
    int hash = 0;
    for (int i = 0; i < m; i++) {
        hash += key[i];
    }
    hash %= n;
    return hash;
}

int Hash2(const char key[m1]) {
    int hash = 0;
    for (int i = 0; i < m; i++) {
        hash += key[i];
    }
    hash %= (n - 1); // Используйте n - 1 для второй хеш-функции
    return (hash + 1); // Убедитесь, что результат всегда больше нуля
}

void sohranka(KeyValuePair t[n]) {
    fstream file("hash.csv", ios_base::out);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        if (t[i].key[0] != '\0') {
            file << i << ";" << t[i].key << ";" << t[i].value << '\n';
        }
    }

    file.close();
}

bool validateKey(const string& key) {
    regex pattern("^[A-Za-z]{2}[0-9]{2}[A-Za-z]{2}$");
    return regex_match(key, pattern);
}

bool add(KeyValuePair t[n], const string& k, const string& v) {
    int id;
    char key[m1];
    strcpy_s(key, m1, k.c_str());
    id = Hash(key);
    int i = 0;

    if (!validateKey(k)) {
        cout << "Неверный формат ключа. Используйте формат ББццББ.\n";
        return false;
    }

    int step = Hash2(key);

    while (i < n) {
        int new_id = (id + i * step) % n;

        // Проверка, существует ли ключ
        if (!strcmp(t[new_id].key, key)) {
            cout << "Ключ уже существует в таблице.\n";
            return false;
        }

        if (!strcmp(t[new_id].key, "\0") || t[new_id].isDeleted) {
            strcpy_s(t[new_id].key, m1, key);
            strcpy_s(t[new_id].value, 50, v.c_str());
            t[new_id].isDeleted = false;
            return true;
        }
        i++;
    }
    return false;
}

short find(KeyValuePair t[n], char k[m1]) {
    int id;
    int step = Hash2(k); // Получите значение второй хеш-функции
    for (unsigned long i = 0; i < n * tour; i++) {
        id = (Hash(k) + i * step) % n; // Вычислите новый индекс с использованием двойного хеширования
        if (id >= n) break;
        if (t[id].isDeleted)
            continue; // Пропускаем удаленные элементы
        if (!strcmp(t[id].key, "\0"))
            return -1;
        if (!strcmp(t[id].key, k))
            return id;
    }
    return -1;
}

bool del(KeyValuePair t[n], const string& k) {
    int id;
    // Преобразуйте строку в массив символов для функции find
    char key[m1];
    strcpy_s(key, m1, k.c_str());
    int index = find(t, key);
    if (index == -1)
        return false;

    // Фактически удаляем ключ
    strcpy_s(t[index].key, m1, "\0");
    strcpy_s(t[index].value, 50, "\0");
    t[index].isDeleted = true;

    return true;
}

void print(KeyValuePair t[n]) {
    for (int i = 0; i < n; i++) {
        if (t[i].key[0] != '\0' && !t[i].isDeleted) { // Проверка, не пустой ли сегмент и не удален ли элемент
            cout << i << ": " << t[i].key << " " << t[i].value << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    KeyValuePair table[n]; // Таблица для хранения пар ключ-значение
    char key[m1]; // ключ
    char value[50]; // значение

    int choice = 12;
    char x[100];

    while (choice != 0) {
        cout << "1. Создать хеш-таблицу\n";
        cout << "2. Добавить элементы в хеш-таблицу\n";
        cout << "3. Просмотреть хеш-таблицу\n";
        cout << "4. Поиск элемента в хеш-таблице\n";
        cout << "5. Удалить элемент в хеш-таблице\n";
        cout << "6. Сохранить хеш таблицу в файл\n";
        cout << "0. Выход\n";
        cout << "\n";

        do {
            cout << "Выберите пункт: ";
            cin >> x;
        } while (!isdigit(x[0]));
        choice = atof(x);
        cout << "--------------------------------------\n";
        cout << "\n";

        switch (choice) {
        case 1: {
            for (int i = 0; i < n; i++) {
                strcpy_s(table[i].key, m1, "\0");
                strcpy_s(table[i].value, 50, "\0");
                table[i].isDeleted = false;
            }
            break;
        }
        case 2: {
            bool t;
            int q = 1;
            int r = 0;
            do {
                for (int i = 0; i < n; i++) {
                    if (table[i].key[0] != '\0' && !table[i].isDeleted) {
                        q = 0;
                    }
                    else {
                        q = 1;
                    }
                }
                if (q == 0) {
                    cout << "Переполнение!\n";
                    break;
                }
                else {
                    do {
                        cout << "Ввод ключа (0 для выхода, формат: ББццББ): ";
                        cin >> key;
                        if (key[0] == '0') {
                            break;
                        }
                        if (!validateKey(key)) {
                            cout << "Неверный формат ключа. Используйте формат ББццББ.\n";
                        }
                        else {
                            break;
                        }
                    } while (1);

                    if (key[0] == '0') {
                        break; // Добавьте эту строку, чтобы выйти из цикла сразу после ввода "0"
                    }

                    cout << "Ввод значения: ";
                    cin >> value;

                    if (add(table, key, value)) {
                        cout << "Добавлено\n";
                    }
                    else {
                        cout << "Ошибка\n";
                    }
                }
            } while (1);
            break;
        }
        case 3: {
            print(table);
            break;
        }
        case 4: {
            cout << "Введите ключ: ";
            cin >> key;
            int index = find(table, key);
            if (index != -1) {
                cout << "Позиция: " << index << "\n";
                cout << "Значение: " << table[index].value << "\n";
            }
            else {
                cout << "Не найден\n";
            }
            break;
        }
        case 5: {
            cout << "Введите ключ: ";
            cin >> key;
            if (del(table, key)) {
                cout << "Удалено\n";
            }
            else {
                cout << "Ошибка\n";
            }
            break;
        }
        case 6: {
            sohranka(table);
            break;
        }
        case 0: {
            break;
        }
        default:
            std::cout << "Ошибка\n";
        }
    }

    system("pause");
    return 0;
}
