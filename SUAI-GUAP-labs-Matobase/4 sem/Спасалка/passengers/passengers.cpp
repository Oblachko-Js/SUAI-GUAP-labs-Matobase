#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <list>
#include <regex>

using namespace std;

const int n = 3000;
const int m1 = 12;

struct KeyValuePair {
    char key[m1];
    char placeAndDate[100];
    char fullName[100];
    char birthDate[20];
    bool isDeleted;
};

int Hash(const char key[m1]) {
    int hash = 0;

    for (int i = 0; i < m1; i++) {
        if (isdigit(key[i])) {
            hash += key[i] - '0'; // Преобразуем символ-цифру в целое число
        }
    }

    hash %= n;
    return hash;
}

void save(list<KeyValuePair> t[]) {
    fstream file("hash.csv", ios_base::out);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        for (const auto& entry : t[i]) {
            if (!entry.isDeleted) {
                file << i << ";";
                file << "Номер паспорта: " << entry.key << ", " << "Место и дата выдачи: " << entry.placeAndDate << ", " << "ФИО: " << entry.fullName << ", " << "Дата рождения: " << entry.birthDate << '\n';
            }
        }
    }

    file.close();
}

void load(list<KeyValuePair> t[]) {
    ifstream file("hash.csv");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        int id;
        ss >> id;
        ss.ignore(); // Пропускаем точку с запятой

        KeyValuePair newEntry;
        string key;

        while (ss >> key) {
            if (key == ";") {
                break; // Завершаем чтение при встрече точки с запятой
            }

            if (key == "Номер") {
                ss >> key; // Пропускаем "паспорта:"
                ss.ignore();
                getline(ss, key, ','); // Читаем номер паспорта до запятой
                strcpy_s(newEntry.key, m1, key.c_str());
            }
            else if (key == "Место") {
                ss >> key; // Пропускаем "и"
                ss >> key; // Читаем "дата"
                ss >> key; // Читаем "выдачи"
                ss.ignore();
                getline(ss, key, ','); // Читаем место выдачи паспорта до запятой
                strcpy_s(newEntry.placeAndDate, 100, key.c_str());
            }
            else if (key == "ФИО:") {
                ss.ignore();
                getline(ss, key, ','); // Читаем ФИО до запятой
                strcpy_s(newEntry.fullName, 100, key.c_str());
            }
            else if (key == "Дата") {
                ss >> key; // Пропускаем "рождения:"
                ss.ignore();
                getline(ss, key, ','); // Читаем дату рождения до запятой
                strcpy_s(newEntry.birthDate, 20, key.c_str());
            }
        }

        newEntry.isDeleted = false;
        t[id].push_back(newEntry);
    }

    file.close();
}

bool validateKey(const string& key) {
    regex pattern("^[0-9]{4}-[0-9]{6}$");
    return regex_match(key, pattern);
}

bool validateFullName(const string& fullName) {
    regex pattern("^[А-Яа-я]+ [А-Яа-я]+ [А-Яа-я]+$");
    return regex_match(fullName, pattern);
}

bool validatePlaceAndDate(const string& placeAndDate) {
    regex pattern("^[А-Яа-я\\-]+ [0-9]{2}.[0-9]{2}.[0-9]{4}$");
    return regex_match(placeAndDate, pattern);
}

bool validateBirthDate(const string& birthDate) {
    regex pattern("^[0-9]{2}.[0-9]{2}.[0-9]{4}$");
    return regex_match(birthDate, pattern);
}

bool isKeyExists(const list<KeyValuePair>& entries, const char* key) {
    for (const auto& entry : entries) {
        if (!strcmp(entry.key, key) && !entry.isDeleted) {
            return true;
        }
    }
    return false;
}

bool add(list<KeyValuePair> t[], const string& k, const string& placeAndDate, const string& fullName, const string& birthDate) {
    if (!validateKey(k)) {
        cout << "Неверный формат ключа. Используйте формат NNNN-NNNNNN.\n";
        return false;
    }

    char key[m1];
    strcpy_s(key, m1, k.c_str());
    int id = Hash(key);

    KeyValuePair newEntry;
    strcpy_s(newEntry.key, m1, key);
    strcpy_s(newEntry.placeAndDate, 100, placeAndDate.c_str());
    strcpy_s(newEntry.fullName, 100, fullName.c_str());
    strcpy_s(newEntry.birthDate, 20, birthDate.c_str());
    newEntry.isDeleted = false;

    t[id].push_back(newEntry);
    return true;
}

KeyValuePair* find(list<KeyValuePair> t[], char k[m1]) {
    int id = Hash(k);

    for (int i = 0; i < n; i++) {
        for (auto& entry : t[i]) {
            if (!strcmp(entry.key, k) && !entry.isDeleted) {
                return &entry;
            }
        }
    }

    return nullptr;  
}

bool del(list<KeyValuePair> t[], const string& k) {
    int id = Hash(k.c_str());

    for (auto& entry : t[id]) {
        if (!strcmp(entry.key, k.c_str())) {
            entry.isDeleted = true;
            return true;
        }
    }

    return false;
}

void print(list<KeyValuePair> t[]) {
    for (int i = 0; i < n; i++) {
        if (!t[i].empty()) {
            cout << i << ": ";
            for (const auto& entry : t[i]) {
                if (!entry.isDeleted) {
                    cout << "Номер паспорта: (" << entry.key << ") Место и дата выдачи: (" << entry.placeAndDate << ") ФИО: (" << entry.fullName << ") Дата рождения: (" << entry.birthDate << "). ";
                }
            }
            cout << endl;
        }
    }
}

int main() {
    system("chcp 1251 > nul");
    srand(time(NULL));
    list<KeyValuePair> table[n];
    char key[m1];
    string placeAndDate;
    string fullName;
    string birthDate;

    // Загрузка данных из файла при запуске программы
    load(table);

    int choice = 12;
    char x[100];

    while (choice != 0) {
        cout << "1. Добавить номер паспорта в хеш-таблицу\n";
        cout << "2. Просмотреть хеш-таблицу\n";
        cout << "3. Поиск номера паспорта в хеш-таблице\n";
        cout << "4. Удалить номер паспорта в хеш-таблице\n";
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
            bool t;
            int q = 1;
            int r = 0;
            while (q != 0) {
                for (int i = 0; i < n; i++) {
                    if (!table[i].empty()) {
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
                    // Ввод ключа
                    cout << "Ввод номера паспорта (0 для выхода, формат: NNNN-NNNNNN) (N - цифра): ";
                    cin >> key;
                    if (key[0] == '0') {
                        break; // Выходим из цикла добавления элементов в хеш-таблицу
                    }

                    while (!validateKey(key) || isKeyExists(table[Hash(key)], key)) {
                        if (!validateKey(key)) {
                            cout << "Неверный ввод.\n";
                        }
                        else {
                            cout << "Такой номер паспорта уже существует в таблице. Введите новый номер паспорта.\n";
                        }
                        cout << "Введите номер паспорта заново (Формат: NNNN-NNNNNN) (N - цифра): ";
                        cin.ignore();  // Очищаем буфер после ввода ключа
                        cin >> key;
                    }

                    // Ввод места и даты выдачи паспорта
                    cout << "Введите место и дату выдачи паспорта (Пример: Санкт-Петербург 20.12.2004): ";
                    cin.ignore(); // Очищаем буфер перед использованием getline
                    getline(cin, placeAndDate);

                    while (!validatePlaceAndDate(placeAndDate)) {
                        cout << "Неверный ввод.\n";
                        cout << "Введите заново (Пример: Санкт-Петербург 20.12.2004): ";
                        getline(cin, placeAndDate);
                    }

                    cout << "Введите ФИО (Пример: Панченко Андрей Викторович): ";
                    getline(cin, fullName);

                    // Ввод ФИО
                    while (!validateFullName(fullName)) {
                        cout << "Неверный ввод.\n";
                        cout << "Введите заново (Пример: Панченко Андрей Викторович): ";
                        getline(cin, fullName);
                    }

                    cout << "Введите дату рождения (Пример: 20.07.2004): ";
                    getline(cin, birthDate);

                    // Ввод даты рождения
                    while (!validateBirthDate(birthDate)) {
                        cout << "Неверный ввод.\n";
                        cout << "Введите заново (Пример: 20.07.2004): ";
                        getline(cin, birthDate);
                    }

                    // Автоматически добавляем ". " в конце даты рождения
                    //birthDate += ". ";

                    if (add(table, key, placeAndDate, fullName, birthDate)) {
                        cout << "Добавлено\n";
                    }
                    else {
                        cout << "Ошибка\n";
                    }
                }
            }
            break;
        }
        case 2: {
            print(table);
            break;
        }
        case 3: {
            cout << "Введите ключ: ";
            cin >> key;
            KeyValuePair* result = find(table, key);
            if (result) {
                cout << "Найдено в сегменте: " << Hash(key) << "\n";
                cout << "Информация о паспорте: (" << result->key << ") " << "Место и дата выдачи: (" << result->placeAndDate << ") ФИО: (" << result->fullName << ") Дата рождения: (" << result->birthDate << ")." << "\n";
            }
            else {
                cout << "Не найдено\n";
            }
            break;
        }
        case 4: {
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
        case 0: {
            break;
        }
        default:
            std::cout << "Ошибка\n";
        }
    }

    save(table);

    system("pause");
    return 0;
}
