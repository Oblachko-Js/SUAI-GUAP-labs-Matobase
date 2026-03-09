#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>

template <typename T>
class GenericArrayOperations {
public:
    GenericArrayOperations(int size, T m1, T m2);
    T CalculateSum();
    void ReplaceLessThan(T threshold, T replacement);
    void MirrorSwap();
    void DivideByTwo();  // Новый метод для деления на 2
    void PrintData(const std::string& label);  // Добавляем метку

private:
    std::vector<T> data;
};

template <typename T>
GenericArrayOperations<T>::GenericArrayOperations(int size, T m1, T m2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(static_cast<float>(m1), static_cast<float>(m2));

    for (int i = 0; i < size; i++) {
        data.push_back(static_cast<T>(dis(gen)));
    }
    DivideByTwo();  // Вызываем новый метод после добавления элементов
}

template <typename T>
void GenericArrayOperations<T>::DivideByTwo() {
    for (T& value : data) {
        value /= 2;
    }
}

template <typename T>
T GenericArrayOperations<T>::CalculateSum() {
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum;
}

template <typename T>
void GenericArrayOperations<T>::ReplaceLessThan(T threshold, T replacement) {
    std::for_each(data.begin(), data.end(), [threshold, replacement](T& value) {
        if (value < threshold) {
            value = T(0);
        }
        });
}

template <typename T>
void GenericArrayOperations<T>::MirrorSwap() {
    if (data.size() >= 4) {
        std::swap(data[0], data[data.size() - 2]);
        std::swap(data[1], data[data.size() - 1]);
    }
}

template <typename T>
void GenericArrayOperations<T>::PrintData(const std::string& label) {
    std::cout << label << " ";
    for (const T& value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    int m1_int = -50, m2_int = 50;
    int k_int = 2, b_int = 5;

    GenericArrayOperations<int> intArray(10, m1_int, m2_int);

    intArray.PrintData("Исходные данные (int):\n");
    intArray.DivideByTwo();
    intArray.PrintData("\nДеление всех элементов на 2 (int):\n");
    intArray.MirrorSwap();
    intArray.PrintData("\nЗеркальный обмен первых двух и двух последних элементов (int):\n");
    intArray.ReplaceLessThan(10, 0);
    intArray.PrintData("\nЗамена элементов меньше 10 на 0 (int):\n");

    float m1_float = -50.0f, m2_float = 50.0f;
    float k_float = 2.0f, b_float = 5.0f;

    GenericArrayOperations<float> floatArray(10, m1_float, m2_float);

    floatArray.PrintData("\nИсходные данные (float):\n");
    floatArray.DivideByTwo();
    floatArray.PrintData("\nДеление всех элементов на 2 (float):\n");
    floatArray.MirrorSwap();
    floatArray.PrintData("\nЗеркальный обмен первых двух и двух последних элементов (float):\n");
    floatArray.ReplaceLessThan(10.0f, 0.0f);
    floatArray.PrintData("\nЗамена элементов меньше 10 на 0 (float):\n");

    return 0;
}
