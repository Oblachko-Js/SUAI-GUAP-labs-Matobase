#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <iostream>
#include <string>
using namespace std;

int negative_sum_func(int* arr, int arr_size);

void composition_func(int& arr_composition, int* arr, int arr_size, bool& elements_within);

void arr_sort(int* arr, int* sorted_arr, int arr_size);

void sort_print(int* arr, int arr_size, string arr_type);

double get_number(string var_name);

int main() {
    setlocale(LC_ALL, "Russian");
    int i, size, composition = 1;
    bool elements_within = true;


    size = get_number("размер");

    int* a = new int[size]; // Операция выделения памяти под массив a

    for (i = 0; i < size; i++) {
        cout << "A[" << i << "] = ";
        cin >> a[i];
    }

    int negative_sum = negative_sum_func(a, size);
    cout << "Сумма отрицательных членов в массиве: " << negative_sum << "\n" << endl;


    composition_func(composition, a, size, elements_within);
    if (elements_within)
        cout << "Произведение между минимальным и максимальным элементами массива = " << composition << "\n\n";
    else
        cout << "Нет элементов между мин. и макс. элементами" << endl;



    int* sorted_a = new int[size]; // Операция выделения памяти под массив sorted_a
    arr_sort(a, sorted_a, size);

    sort_print(a, size, "Изначальный");
    sort_print(sorted_a, size, "Отсортированный");


    delete[] sorted_a; // Освобождение памяти, выделенной под массив sorted_a
    delete[] a; // Освобождение памяти, выделенной под массив a

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
    return 0;
}


int negative_sum_func(int* arr, int arr_size) {
    int i, arr_negative_sum = 0;

    for (i = 0; i < arr_size; i++) {

        if (arr[i] < 0)
            arr_negative_sum += arr[i];
    }
    return arr_negative_sum;
}

void composition_func(int& arr_composition, int* arr, int arr_size, bool& elements_within) {
    int max = 0, k_min = 0, k_max = 0, i, min = arr[0];

    for (i = 0; i < arr_size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            k_min = i;
        }

        if (arr[i] > max) {
            max = arr[i];
            k_max = i;
        }
    }

    if (abs(k_max - k_min) == 1)
        elements_within = false;

    if (elements_within) {
        if (k_max > k_min) {
            for (i = k_min + 1; i < k_max; i++)
                arr_composition *= arr[i];
        }
        else {
            for (i = k_max + 1; i < k_min; i++)
                arr_composition *= arr[i];
        }
    }
}

void arr_sort(int* arr, int* sorted_arr, int arr_size) {
    int i, j, temp;

    for (i = 0; i < arr_size; i++)
        sorted_arr[i] = arr[i];

    for (i = 0; i < arr_size - 1; i++) {
        for (j = 0; j < arr_size - 1 - i; j++) {
            if (sorted_arr[j] > sorted_arr[j + 1]) {
                temp = sorted_arr[j + 1];
                sorted_arr[j + 1] = sorted_arr[j];
                sorted_arr[j] = temp;
            }
        }
    }
}

void sort_print(int* arr, int arr_size, string arr_type) {
    int i;
    cout << arr_type << " массив:" << endl;

    cout << "[";
    for (i = 0; i < arr_size; i++) {
        cout << "" << arr[i];
        if ((arr_size - i - 1) != 0) {
            cout << ", ";
        }
        else
            cout << " ";
    }
    cout << "]\n\n";

}

double get_number(string var_name) {
    double arg;
    cout << "Введите " << var_name << ": ";

    while (!(cin >> arg)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Вы ввели не число!" << endl << "Введите " << var_name << ": ";
    }
    return arg;
}
