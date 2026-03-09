#include <iostream>
using namespace std;

void outputMatrix(int** matrix, int rows, int columns);
void countNonZeroRows(int** matrix, int rows, int columns);
int findMaxDuplicate(int** matrix, int rows, int columns);

int main() {
    setlocale(LC_ALL, "Russian");
    int rows, columns;

    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> columns;

    // Выделение памяти под матрицу
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }

    // Ввод элементов матрицы
    cout << "Введите элементы матрицы:" << "\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }
    cout << endl;


    outputMatrix(matrix, rows, columns);

    // Вызов функций для решения задачи
    countNonZeroRows(matrix, rows, columns);
    int maxDuplicate = findMaxDuplicate(matrix, rows, columns);
    cout << "Максимальное число, встречающееся более одного раза: " << maxDuplicate << endl;

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    } delete[] matrix;
    return 0;
}



//Функция для вывода матрицы
void outputMatrix(int** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}


// Функция для подсчета количества строк, не содержащих ни одного нулевого элемента
void countNonZeroRows(int** matrix, int rows, int columns) {
    int nonZeroRows = 0;
    for (int i = 0; i < rows; i++) {
        bool hasZero = false;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (!hasZero) {
            nonZeroRows++;
        }
    }
    cout << "Количество строк, не содержащих ни одного нулевого элемента: " << nonZeroRows << endl;
}

// Функция для нахождения максимального числа, встречающегося более одного раза
int findMaxDuplicate(int** matrix, int rows, int columns) {
    int maxDuplicate = INT_MIN;
    int* count = new int[1000001]; // Максимальное значение элемента в матрице ограничено 1.000.000

    for (int i = 0; i <= 1000000; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            count[matrix[i][j]]++;
        }
    }

    for (int i = 0; i <= 1000000; i++) {
        if (count[i] > 1 && i > maxDuplicate) {
            maxDuplicate = i;
        }
    }

    delete[] count;

    return maxDuplicate;
}
