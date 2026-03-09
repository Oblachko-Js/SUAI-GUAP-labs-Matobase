#include <iostream>
#include <vector>
#include <algorithm>

class MyException : public std::exception {
public:
    MyException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    std::string message_;
};

class Massiv {
private:
    std::vector<int> arr;
    int length;

public:
    Massiv();

    int productOfEvenIndexedElements();

    int sumBetweenZeros();

    void printArray();

    void transformArray();

    void printTransformedArray();
};

Massiv::Massiv() {
    int studentCode;
    std::cout << "Введите ваш шифр студента(если сумма двух последних цифр меньше 12, то размер массива будет 12): ";

    try {
        std::cin >> studentCode;
        if (std::cin.fail()) {
            throw MyException("Ошибка ввода. Неправильный формат данных.");
        }

        int lastTwoDigits = (studentCode % 100) / 10 + (studentCode % 10); // Складываем последние две цифры.
        length = (lastTwoDigits >= 12) ? lastTwoDigits : 12;

        std::cout << "Введите " << length << " элементов массива:\n";

        for (int i = 0; i < length; ++i) {
            int element;

            // Try-catch block for input validation
            try {
                std::cin >> element;

                if (std::cin.fail()) {
                    throw MyException("Ошибка ввода элемента. Неправильный формат данных.");
                }

                arr.push_back(element);
            }
            catch (const MyException& e) {
                std::cerr << "Ошибка ввода элемента: " << e.what() << std::endl;
                // Clear input buffer to prevent an infinite loop on invalid input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                --i; // Re-enter the current element
            }
        }
    }
    catch (const MyException& e) {
        std::cerr << "Ошибка ввода шифра студента: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // You might want to add a default value for length in case of an exception
        length = 0;
    }
}

int Massiv::productOfEvenIndexedElements() {
    int product = 1;
    for (int i = 1; i < length; i += 2) {
        product *= arr[i];
    }
    return product;
}

int Massiv::sumBetweenZeros() {
    int firstZeroIndex = -1;
    int lastZeroIndex = -1;

    for (int i = 0; i < length; ++i) {
        if (arr[i] == 0) {
            if (firstZeroIndex == -1) {
                firstZeroIndex = i;
            }
            lastZeroIndex = i;
        }
    }

    if (firstZeroIndex == -1 || lastZeroIndex == -1) {
        throw MyException("Нет нулевых элементов в массиве");
    }

    int sum = 0;
    for (int i = firstZeroIndex + 1; i < lastZeroIndex; ++i) {
        sum += arr[i];
    }

    return sum;
}

void Massiv::printArray() {
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void Massiv::transformArray() {
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        if (a >= 0 && b >= 0) {
            return a < b;
        }
        if (a < 0 && b < 0) {
            return a > b;
        }
        return a >= 0;
        });
}

void Massiv::printTransformedArray() {
    std::cout << "Преобразованный массив: ";
    for (int i = 0; i < length; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    system("chcp 1251 > nul");
    system("color 71");

    try {
        Massiv myArray;
        std::cout << "Произведение элементов с четными номерами: " << myArray.productOfEvenIndexedElements() << std::endl;
        try {
            std::cout << "Сумма элементов между первым и последним нулевыми элементами: " << myArray.sumBetweenZeros() << std::endl;
        }
        catch (const MyException& e) {
            std::cerr << "Ошибка в sumBetweenZeros: " << e.what() << std::endl;
        }
        // Преобразование массива
        myArray.transformArray();
        myArray.printTransformedArray();
    }
    catch (const MyException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}

