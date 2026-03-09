#include <iostream>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>
#include <limits> // Для использования numeric_limits

using namespace std;

// Функция для вывода списка на экран
template <typename T>
void printList(const list<T>& lst) {
    for (const T& item : lst) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали для отображения русских букв

    list<int> s, t, u; // Создаем три последовательности символов как список целых чисел
    int k, m, n;

    // Ввод количества элементов в каждой последовательности
    cout << "Введите количество элементов в последовательности s: ";
    cin >> k;
    cout << "Введите элементы последовательности s: ";
    for (int i = 0; i < k; i++) {
        int element;
        cin >> element;
        s.push_back(element);
    }

    // Очищаем входной буфер
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Введите количество элементов в последовательности t: ";
    cin >> m;
    cout << "Введите элементы последовательности t: ";
    for (int i = 0; i < m; i++) {
        int element;
        cin >> element;
        t.push_back(element);
    }

    // Очищаем входной буфер
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Введите количество элементов в последовательности u: ";
    cin >> n;
    cout << "Введите элементы последовательности u: ";
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        u.push_back(element);
    }

    // Очищаем входной буфер
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    list<int> commonElements;
    for (int num : s) {
        if (count(t.begin(), t.end(), num) > 0 && count(u.begin(), u.end(), num) > 0) {
            commonElements.push_back(num);
        }
    }

    commonElements.sort();
    commonElements.unique();

    // Выводим результат
    cout << "Результат: ";
    printList(commonElements);

    // Меню для изменения результата
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить число" << endl;
        cout << "2. Удалить число по позиции" << endl;
        cout << "3. Завершить программу" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            int numToAdd;
            cout << "Введите число для добавления: ";
            cin >> numToAdd;
            commonElements.push_back(numToAdd);
            commonElements.sort();
            commonElements.unique();
            cout << "Результат: ";
            printList(commonElements);
        }
        else if (choice == 2) {
            int positionToRemove;
            cout << "Введите позицию числа для удаления (0-based): ";
            cin >> positionToRemove;
            if (positionToRemove >= 0 && positionToRemove < commonElements.size()) {
                auto it = commonElements.begin();
                advance(it, positionToRemove);
                commonElements.erase(it);
                cout << "Результат: ";
                printList(commonElements);
            }
            else {
                cout << "Некорректная позиция. Попробуйте снова." << endl;
            }
        }
        else if (choice == 3) {
            break; // Завершаем программу
        }
        else {
            cout << "Некорректный выбор. Попробуйте снова." << endl;
        }
    }

    return 0;
}
