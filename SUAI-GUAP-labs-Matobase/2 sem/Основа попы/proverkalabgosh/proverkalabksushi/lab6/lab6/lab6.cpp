#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

using namespace std;

// Функция подсчета количества локальных минимумов
int localMin(int** a, int n) {
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 || a[i][j] < a[i - 1][j]) &&
                (j == 0 || a[i][j] < a[i][j - 1]) &&
                (i == n - 1 || a[i][j] < a[i + 1][j]) &&
                (j == n - 1 || a[i][j] < a[i][j + 1])) {
                k++;
            }
        }
    }
    return k;
}


// Функция подсчета суммы модулей элементов выше главной диагонали
int sumdiag(int** a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += abs(a[i][j]);
        }
    }
    return sum;
}

bool valid(int n) {
    if (n <= 0 || cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Некорректный размер матрицы! Введите целое неотрицательное число" << endl;
        return false;
    }
    return true;
}
int  checkelem() {
    int inp;
    cin >> inp;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Значение должно быть целым числом." << endl;
        cout << "Повторите ввод!" << endl;
        cin >> inp;
    }
    return inp;
}


int main() {
    setlocale(LC_ALL, "rus");
    int n;
    do {
        cout << "Введите размер матрицы: ";
        cin >> n;
    } while (!valid(n));

    // Создаем динамический двумерный массив размером n на n
    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }


    // Вводим матрицу с клавиатуры
    cout << "Введите элементы матрицы:\n";
    for (int i = 0; i < n; i++) {
        cout << "Введите элементы " << i + 1 << "-ой строки через пробел: ";
        for (int j = 0; j < n; j++) {
            a[i][j] = checkelem();
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }

    // Вызываем функции подсчета и выводим результаты
    int k = localMin(a, n);
    cout << "Количество локальных минимумов: " << k << endl;

    int sum = sumdiag(a, n);
    cout << "Сумма модулей элементов выше главной диагонали: " << sum << endl;

    // Освобождаем выделенную под массив память
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    // Для обнаружения утечек памяти
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();

    return 0;
}
