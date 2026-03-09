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

bool valid(int n) {
	if (n <= 0 || cin.fail()) {

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Некорректный размер массива! Введите целое неотрицательное число" << endl;
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

int MinAbs(int* arr, int n) {
	int minAbs = abs(*arr);// Инициализация минимального значения модуля первым элементом массива
	for (int i = 1; i < n; i++) {
		if (abs(*(arr + i)) < minAbs) {
			minAbs = abs(*(arr + i));
		}
	}
	return minAbs;
}

int sumAfterZero(int* arr, int n) {
	int sum = 0;
	int firstInd = -1;
	bool foundZero = false;

	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			if (!foundZero) {
				foundZero = true;
				firstInd = i;
			}
			else {
				sum += abs(arr[i]);
			}
		}
		else {
			if (foundZero) {
				sum += abs(arr[i]);
			}
		}
	}

	if (!foundZero || (firstInd == n - 1)) {
		cout << "Ошибка: невозможно найти сумму.\n";
	}
	return sum;
}


void transform(int* arr, int n, int* newArr) {
	int even = 0;
	int odd = (n + 1) / 2;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			*(newArr + even) = *(arr + i);
			even++;
		}
		else {
			*(newArr + odd) = *(arr + i);
			odd++;
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	int n;
	do {
		cout << "Введите количество элементов массива: ";
		cin >> n;
	} while (!valid(n));

	int* arr = new int[n];


	for (int i = 0; i < n; i++) {

		cout << "Введите " << i + 1 << " элемент массива: ";
		arr[i] = checkelem();

	}

	int minAbs = MinAbs(arr, n);
	cout << "Минимальный по модулю элемент массива: " << minAbs << endl;

	int sum = sumAfterZero(arr, n);
	cout << "Сумма модулей элементов после первого нуля: " << sum << "\n";


	int* newArr = new int[n];
	transform(arr, n, newArr);
	cout << "Преобразованный массив: ";
	for (int i = 0; i < n; i++) {
		cout << *(newArr + i) << " ";
	}
	cout << endl;

	delete[] arr;
	delete[] newArr;
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
