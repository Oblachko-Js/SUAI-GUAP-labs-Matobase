#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <regex>

using namespace std;

const int INITIAL_TABLE_SIZE = 3000;

struct Node {
    string key;
    string data;
};

class HashTable {
private:
    vector<vector<Node>> table;
    int tableSize; // Размер таблицы

    unsigned int hashFunction(const string& key, int size) {
        unsigned int hash = 0;
        for (char c : key) {
            hash = (hash * 31) + c;
        }
        return hash % size;
    }

    unsigned int quadraticProbe(unsigned int index, unsigned int attempt, int size) {
        return (index + attempt * attempt) % size;
    }

public:
    HashTable() {
        tableSize = INITIAL_TABLE_SIZE;
        table.resize(tableSize);
    }

    void createTable() {
        table.clear();
        tableSize = INITIAL_TABLE_SIZE;
        table.resize(tableSize);
    }

    void insert(const string& key, const string& data) {
        int id;
        id = hashi(k);
        int i = 0; // Счетчик для квадратичного опробования
        while (i < n) {
            int new_id = (id + i * i) % n;
            if (!strcmp(t[new_id], "\0")) {
                strcpy_s(t[new_id], m1, k);
                return true;
            }
            i++; // Увеличиваем i квадратично
        }
    }

    bool search(const string& key, string& data) {
        unsigned int index = hashFunction(key, tableSize);
        unsigned int attempt = 0;

        while (attempt < tableSize) {
            if (table[index].empty()) {
                return false;
            }
            if (table[index].back().key == key) {
                data = table[index].back().data;
                return true;
            }
            index = quadraticProbe(index, attempt, tableSize);
            attempt++;
        }
        return false;
    }

    bool searchBySegment(int segmentNumber, vector<Node>& result) {
        if (segmentNumber < 0 || segmentNumber >= tableSize) {
            return false;
        }
        result = table[segmentNumber];
        return true;
    }

    void remove(const string& key) {
        unsigned int index = hashFunction(key, tableSize);
        unsigned int attempt = 0;

        while (attempt < tableSize) {
            if (table[index].empty()) {
                return;
            }
            if (table[index].back().key == key) {
                table[index].pop_back();
                return;
            }
            index = quadraticProbe(index, attempt, tableSize);
            attempt++;
        }
    }

    void saveToCSV(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const vector<Node>& segment : table) {
                for (const Node& node : segment) {
                    outFile << node.key << "," << node.data << endl;
                }
            }
            outFile.close();
            cout << "Данные сохранены в файл " << filename << endl;
        }
        else {
            cerr << "Ошибка при открытии файла для записи." << endl;
        }
    }

    void handleOverflow() {
        int newSize = tableSize * 2; // Увеличиваем размер вдвое
        vector<vector<Node>> newTable(newSize);

        // Перехеширование существующих данных
        for (int i = 0; i < tableSize; ++i) {
            for (const Node& node : table[i]) {
                unsigned int index = hashFunction(node.key, newSize);
                unsigned int attempt = 0;

                while (!newTable[index].empty()) {
                    index = quadraticProbe(index, attempt, newSize);
                    attempt++;
                }

                newTable[index].push_back(node);
            }
        }

        // Заменяем старую таблицу на новую
        table = move(newTable);
        tableSize = newSize;
    }

    bool validateKey(const string& key) {
        regex pattern("^[A-Za-z][0-9]{3}[A-Za-z]{2}$");
        return regex_match(key, pattern);
    }

    void displayTable() {
        for (int i = 0; i < tableSize; ++i) {
            if (!table[i].empty()) {
                cout << "Сегмент " << i << ": ";
                for (const Node& node : table[i]) {
                    cout << "[" << node.key << ": " << node.data << "] ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    HashTable hashTable;
    string key, data;
    int choice;

    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Создать хеш-таблицу" << endl;
        cout << "2. Добавить элемент" << endl;
        cout << "3. Просмотреть хеш-таблицу" << endl;
        cout << "4. Поиск элемента" << endl;
        cout << "5. Выгрузить в файл" << endl;
        cout << "6. Удалить элемент" << endl;
        cout << "7. Выход" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            hashTable.createTable();
            cout << "Хеш-таблица создана." << endl;
            break;
        case 2:
            cout << "Введите ключ в формате БцццББ(Б - буква, ц - цифра): ";
            cin >> key;
            // Проверка формата ключа
            if (!hashTable.validateKey(key)) {
                cout << "Неверный формат ключа. Формат должен быть БцццББ." << endl;
                break;
            }
            cout << "Введите данные: ";
            cin >> data;
            hashTable.insert(key, data);
            break;
        case 3:
            hashTable.displayTable();
            break;
        case 4:
            cout << "Введите ключ для поиска: ";
            cin >> key;
            if (hashTable.search(key, data)) {
                cout << "Найден элемент с данными: " << data << endl;
            }
            else {
                cout << "Элемент не найден." << endl;
            }
            break;
        case 5:
            cout << "Введите имя файла для сохранения данных: ";
            cin >> key;
            hashTable.saveToCSV(key);
            break;
        case 6:
            cout << "Введите ключ для удаления: ";
            cin >> key;
            hashTable.remove(key);
            break;
        case 7:
            return 0;
        default:
            cout << "Недопустимая команда. Пожалуйста, выберите корректное действие." << endl;
            break;
        }
    }
    return 0;
}
