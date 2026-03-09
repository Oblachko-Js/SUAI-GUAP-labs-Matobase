#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

template<typename T>
class GenericArrayOperations {
public:
    GenericArrayOperations(int size, T m1, T m2);
    T CalculateSum();
    void ApplyOperation(T k, T b);
    void ReplaceGreaterThan(T threshold, T replacement);
    void PrintDataWithOriginal();
    void PrintOriginalData();

private:
    std::vector<T> data;
    std::vector<T> originalData; // Вектор для хранения исходных данных
};

template<typename T>
GenericArrayOperations<T>::GenericArrayOperations(int size, T m1, T m2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(static_cast<double>(m1), static_cast<double>(m2));

    for (int i = 0; i < size; i++) {
        T value = static_cast<T>(dis(gen));
        data.push_back(value);
        originalData.push_back(value); // Сохраняем исходные данные
    }
}

template<typename T>
T GenericArrayOperations<T>::CalculateSum() {
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum;
}

template<typename T>
void GenericArrayOperations<T>::ApplyOperation(T k, T b) {
    for (int i = 0; i < data.size(); i++) {
        data[i] = k * data[i] + b;
    }
}

template<typename T>
void GenericArrayOperations<T>::ReplaceGreaterThan(T threshold, T replacement) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i] > threshold) {
            originalData[i] = data[i]; // Сохраняем исходное значение
            data[i] = replacement; // Применяем замену
        }
    }
}

template<typename T>
void GenericArrayOperations<T>::PrintDataWithOriginal() {
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << "(" << originalData[i] << ") "; // Выводим исходное число рядом с преобразованным
    }
    std::cout << std::endl;
}

template<typename T>
void GenericArrayOperations<T>::PrintOriginalData() {
    for (int i = 0; i < originalData.size(); i++) {
        std::cout << originalData[i] << " "; // Выводим только исходные значения
    }
    std::cout << std::endl;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    int m1_int = 0, m2_int = 10;
    int k_int = 2, b_int = 5;

    GenericArrayOperations<int> intArray(10, m1_int, m2_int);

    std::cout << "Исходные данные (int): \n";
    intArray.PrintOriginalData();

    int sum_int = intArray.CalculateSum();
    std::cout << "Сумма элементов (int): \n" << sum_int << std::endl;

    std::cout << "Результат после операции x = " << k_int << " * x + " << b_int << " (int): \n";
    intArray.ApplyOperation(k_int, b_int);
    intArray.PrintDataWithOriginal();

    intArray.ReplaceGreaterThan(20, 10);
    std::cout << "Результат после замены элементов больше 20 на 10 (int): \n";
    intArray.PrintDataWithOriginal();

    float m1_float = 0.0f, m2_float = 10.0f;
    float k_float = 2.0f, b_float = 5.0f;

    GenericArrayOperations<float> floatArray(10, m1_float, m2_float);

    std::cout << "Исходные данные (float): \n";
    floatArray.PrintOriginalData();

    float sum_float = floatArray.CalculateSum();
    std::cout << "Сумма элементов (float): \n" << sum_float << std::endl;

    std::cout << "Результат после операции x = " << k_float << " * x + " << b_float << " (float): \n";
    floatArray.ApplyOperation(k_float, b_float);
    floatArray.PrintDataWithOriginal();

    floatArray.ReplaceGreaterThan(20.0f, 10.0f);
    std::cout << "Результат после замены элементов больше 20 на 10 (float): \n";
    floatArray.PrintDataWithOriginal();

    return 0;
}
