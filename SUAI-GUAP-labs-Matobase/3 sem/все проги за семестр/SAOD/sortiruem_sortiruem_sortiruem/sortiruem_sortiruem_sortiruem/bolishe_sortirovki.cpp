#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Глобальные переменные для подсчета сравнений и перестановок
int comparisons = 0;
int swaps = 0;

// Функция для вывода массива на экран
void printArray(const vector<int>& arr){
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Функция для поиска элемента в массиве по его содержимому
vector<int> searchByValue(const vector<int>& arr, int value) {
    vector<int> positions;
    for (int i = 0; i < arr.size(); ++i) {
        comparisons++;
        if (arr[i] == value) {
            positions.push_back(i);
        }
    }
    return positions;
}

// Функция для поиска элемента в массиве по его порядковой позиции
int searchByPosition(const vector<int>& arr, int position) {
    if (position >= 0 && position < arr.size()) {
        return arr[position];
    }
    return -1; // Позиция недопустима
}

// Функция для добавления элемента и пересортировки массива
void insertAndSort(vector<int>& arr, int value) {
    arr.push_back(value);
    int n = arr.size();
    int i = n - 1;
    comparisons++;
    while (i > 0 && arr[i - 1] > value) {
        comparisons++;
        swaps++;
        arr[i] = arr[i - 1];
        i--;
    }
    arr[i] = value;
}

// Функция для удаления элемента и пересортировки массива
void removeAndSort(vector<int>& arr, int value) {
    auto it = find(arr.begin(), arr.end(), value);
    if (it != arr.end()) {
        arr.erase(it);
        sort(arr.begin(), arr.end());
    }
}

// Алгоритм шейкерной сортировки
void shakerSort(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        for (int i = left; i < right; ++i) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swaps++;
                swap(arr[i], arr[i + 1]);
            }
        }
        right--;

        for (int i = right; i > left; --i) {
            comparisons++;
            if (arr[i - 1] > arr[i]) {
                swaps++;
                swap(arr[i - 1], arr[i]);
            }
        }
        left++;
    }
}

// Функция для подсчета количества различных чисел в массиве
int countUniqueNumbers(const vector<int>& arr) {
    set<int> uniqueNumbers;
    for (int num : arr) {
        uniqueNumbers.insert(num);
    }
    return uniqueNumbers.size();
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> A(n);
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    while (true) {
        cout << "Выберите операцию:" << endl;
        cout << "1. Поиск элемента по значению" << endl;
        cout << "2. Поиск элемента по порядковой позиции" << endl;
        cout << "3. Добавление элемента" << endl;
        cout << "4. Удаление элемента" << endl;
        cout << "5. Отсортировать массив" << endl;
        cout << "6. Вывести массив" << endl;
        cout << "7. Вывести количество сравнений и перестановок" << endl;
        cout << "8. Завершить программу" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int searchValue;
            cout << "Введите значение для поиска: ";
            cin >> searchValue;
            vector<int> positions = searchByValue(A, searchValue);
            if (!positions.empty()) {
                cout << "Элемент " << searchValue << " найден на позициях: ";
                for (int position : positions) {
                    cout << position << " ";
                }
                cout << endl;
            }
            else {
                cout << "Элемент " << searchValue << " не найден" << endl;
            }
            break;
        }
        case 2: {
            int position;
            cout << "Введите порядковую позицию для поиска: ";
            cin >> position;
            int element = searchByPosition(A, position);
            if (element != -1) {
                cout << "Элемент на позиции " << position << ": " << element << endl;
            }
            else {
                cout << "Позиция недопустима" << endl;
            }
            break;
        }
        case 3: {
            int insertValue;
            cout << "Введите элемент для добавления: ";
            cin >> insertValue;
            insertAndSort(A, insertValue);
            cout << "Массив после добавления элемента: ";
            printArray(A);
            break;
        }
        case 4: {
            int removeValue;
            cout << "Введите элемент для удаления: ";
            cin >> removeValue;
            removeAndSort(A, removeValue);
            cout << "Массив после удаления элемента: ";
            printArray(A);
            break;
        }
        case 5: {
            shakerSort(A);
            cout << "Массив отсортирован." << endl;
            break;
        }
        case 6: {
            cout << "Текущий массив: ";
            printArray(A);
            break;
        }
        case 7: {
            cout << "Количество сравнений: " << comparisons << endl;
            cout << "Количество перестановок: " << swaps << endl;
            int uniqueCount = countUniqueNumbers(A); // Вызываем функцию для подсчета уникальных чисел
            cout << "Количество различных чисел в массиве: " << uniqueCount << endl;
            break;
        }
        case 8: {
            cout << "Программа завершена." << endl;
            return 0;
        }
        default: {
            cout << "Неверный выбор операции. Пожалуйста, выберите снова." << endl;
        }
        }
    }

    return 0;
}
