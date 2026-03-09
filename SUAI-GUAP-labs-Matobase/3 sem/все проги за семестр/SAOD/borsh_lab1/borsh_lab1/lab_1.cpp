#include <iostream>
#include <ctime>

int n;

void set_array(int* A) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 101 - 50; // Генерируем случайные числа от -50 до 50
    }
}

int count_zeros(int* A) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));
    std::cout << "Программа создана Борщем Н.С." << std::endl;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    int* A = new int[n];
    set_array(A);

    int choice;
    int zero_count = 0; // Объявляем zero_count здесь

    // Вывод элементов массива
    std::cout << "Элементы массива: ";
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Выберите операцию:\n";
    std::cout << "1. Уменьшить все четные элементы вдвое\n";
    std::cout << "2. Подсчитать количество элементов с нулевым значением\n";
    std::cin >> choice;

    switch (choice) {
    case 1:
        // Уменьшаем все четные значения вдвое
        for (int i = 0; i < n; i++) {
            if (A[i] % 2 == 0) {
                A[i] /= 2;
            }
        }

        // Вывод измененных элементов
        std::cout << "Элементы массива после уменьшения четных вдвое: ";
        for (int i = 0; i < n; i++) {
            std::cout << A[i] << " ";
        }
        std::cout << std::endl;
        break;

    case 2:
        // Подсчитываем количество элементов с нулевым значением
        zero_count = count_zeros(A);
        std::cout << "Количество элементов с нулевым значением: " << zero_count << std::endl;
        break;

    default:
        std::cout << "Некорректный выбор операции." << std::endl;
        break;
    }

    delete[] A;
    return 0;
}
