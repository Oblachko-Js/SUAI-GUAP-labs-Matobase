#include <iostream>
#include <vector>
#include <algorithm>

class Massiv {
private:
    std::vector<double> arr;

public:
    Massiv(int n);

    double maxAbsoluteElement();

    double sumBetweenPositiveElements();

    void transformArray();

    void printTransformedArray();
};

Massiv::Massiv(int n) {
    arr.resize(n);

    std::cout << "Введите " << n << " вещественных элементов массива:\n";
    for (int i = 0; i < n; ++i) {
        double element;
        std::cin >> element;
        arr[i] = element;
    }
}

double Massiv::maxAbsoluteElement() {
    if (arr.empty()) {
        throw std::runtime_error("Массив пуст");
    }

    double maxAbs = std::abs(arr[0]);
    for (const double& element : arr) {
        double absElement = std::abs(element);
        if (absElement > maxAbs) {
            maxAbs = absElement;
        }
    }
    return maxAbs;
}

double Massiv::sumBetweenPositiveElements() {
    int firstPositiveIndex = -1;
    int secondPositiveIndex = -1;

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > 0) {
            if (firstPositiveIndex == -1) {
                firstPositiveIndex = i;
            }
            else if (secondPositiveIndex == -1) {
                secondPositiveIndex = i;
                break;
            }
        }
    }

    if (firstPositiveIndex == -1 || secondPositiveIndex == -1) {
        throw std::runtime_error("Недостаточно положительных элементов в массиве");
    }

    double sum = 0;
    for (int i = firstPositiveIndex + 1; i < secondPositiveIndex; ++i) {
        sum += arr[i];
    }

    return sum;
}

void Massiv::transformArray() {
    std::sort(arr.begin(), arr.end(), [](double a, double b) {
        if (a == 0) {
            return false;
        }
        else if (b == 0) {
            return true;
        }
        else {
            return a < b;
        }
        });
}

void Massiv::printTransformedArray() {
    std::cout << "Преобразованный массив: ";
    for (const double& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");
    int n;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> n;

    try {
        Massiv myArray(n);

        try {
            std::cout << "Максимальный по модулю элемент массива: " << myArray.maxAbsoluteElement() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        try {
            std::cout << "Сумма элементов между первым и вторым положительными элементами: " << myArray.sumBetweenPositiveElements() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        myArray.transformArray();
        myArray.printTransformedArray();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
