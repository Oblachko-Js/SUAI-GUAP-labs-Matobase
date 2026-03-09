//lab5 var 18
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Глобальные переменные для подсчета сравнений и перестановок
int comparisons = 0;
int swaps = 0;

// Функция для вывода массива на экран
void printArray(const vector<int>& arr) {
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

// Функция для слияния двух отсортированных подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            swaps++;
            arr[k] = leftArr[i];
            i++;
        }
        else {
            swaps++;
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        swaps++;
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        swaps++;
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Функция для сортировки слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Функция для добавления элемента и сортировки массива с использованием сортировки слиянием
void insertAndSort(vector<int>& arr, int value) {
    arr.push_back(value);
    mergeSort(arr, 0, arr.size() - 1);
}

// Функция для удаления элемента и сортировки массива с использованием сортировки слиянием
void removeAndSort(vector<int>& arr, int value) {
    auto it = find(arr.begin(), arr.end(), value);
    if (it != arr.end()) {
        arr.erase(it);
        mergeSort(arr, 0, arr.size() - 1);
    }
}

// Функция для подсчета количества повторяющихся чисел в массиве
int countDuplicateNumbers(const vector<int>& arr) {
    map<int, int> frequencyMap;
    int duplicatesCount = 0;

    for (int num : arr) {
        // Увеличиваем частоту числа в map
        frequencyMap[num]++;
    }

    // Подсчитываем количество повторений
    for (const auto& pair : frequencyMap) {
        if (pair.second > 1) {
            duplicatesCount++;
        }
    }

    return duplicatesCount;
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
            mergeSort(A, 0, A.size() - 1);
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
            int duplicateCount = countDuplicateNumbers(A); // Вызываем функцию для подсчета повторяющихся чисел
            cout << "Количество повторяющихся чисел в массиве: " << duplicateCount << endl;
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
