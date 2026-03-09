#include <iostream>
#include <cstring>
using namespace std;

// Функция для определения длины строки
int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Функция для копирования строки в другую строку заданное количество раз
char* copyString(const char* str, int repetitions) {
    int originalLength = stringLength(str);
    int newLength = originalLength * repetitions;
    char* result = new char[newLength + 1];
    int index = 0;
    for (int i = 0; i < repetitions; i++) {
        for (int j = 0; j < originalLength; j++) {
            result[index++] = str[j];
        }
    }
    result[newLength] = '\0';

    return result;
}

int main() {
    setlocale(LC_ALL, "");
    cout << "Введите строку: ";
    char originalString[100];
    cin.getline(originalString, 100);
    int repetitions;
    do {
        cout << "Введите количество повторений: ";
        cin >> repetitions;
    } 
    while (repetitions < 1);
    char* copiedString = copyString(originalString, repetitions);
    cout << "Строка: " << originalString << endl;
    cout << "Количество повторений: " << repetitions << endl;
    cout << "Результирующая строка: " << copiedString << endl;
    delete[] copiedString;
    return 0;
}
