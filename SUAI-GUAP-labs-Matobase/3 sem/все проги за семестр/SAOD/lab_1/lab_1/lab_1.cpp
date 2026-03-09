#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale>

using namespace std;

const int MAX_N = 1000; // Максимальный размер массива

// Функция для заполнения массива случайными значениями в заданном диапазоне
void fillArray(int A[], int n) {
    int minVal = -((n / 2) - 1);
    int maxVal = n / 2;
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
}

// Функция для подсчета суммы отрицательных элементов (O(n))
int sumNegativeElements(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            sum += A[i];
        }
    }
    return sum;
}

// Функция для подсчета количества отрицательных элементов (O(1))
int countNegativeElements(int A[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    int n;
    cout << "Введите размер массива (n): ";
    while (!(cin >> n) || n <= 0 || n > MAX_N) {
        cin.clear(); // Очищаем флаг ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
        cout << "Некорректный размер массива. Пожалуйста, введите положительное число до " << MAX_N << ": ";
    }

    int A[MAX_N];
    fillArray(A, n);

    cout << "Случайные значения массива A:" << endl;
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    int choice;
    cout << "Выберите функцию (1 - сумма отрицательных, 2 - количество отрицательных): ";
    cin >> choice;

    if (choice == 1) {
        int sum = sumNegativeElements(A, n);
        cout << "Сумма отрицательных элементов: " << sum << endl;
    }
    else if (choice == 2) {
        int count = countNegativeElements(A, n);
        cout << "Количество отрицательных элементов: " << count << endl;
    }
    else {
        cout << "Некорректный выбор функции. Выберите 1 или 2." << endl;
        return 1;
    }

    return 0;
}
