#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void F(double a, double b, double c, double x, bool* flag, double* res); // объявляем функцию F с передачей по указателю

double get_number(char var_name);

int main() {
	setlocale(LC_ALL, "Russian");
	double a, b, c, x, y, d;
	double res = 0;
	bool flag = false;

	a = get_number('a');
	b = get_number('b');
	c = get_number('c');
	x = get_number('x');
	y = get_number('y');
	d = get_number('d');

	for (double cur_x = x; cur_x <= y; cur_x += d) {
		F(a, b, c, cur_x, &flag, &res);
		cout << a;
		if (flag)
			cout << "Ошибка: Деление на ноль при x=" << cur_x << "!" << endl; // выводим значение текущего x при ошибке
		else
			cout << "Значение F при x=" << cur_x << " = " << res << endl;
		flag = false;
	}

	return 0;
}

void F(double a, double b, double c, double x, bool* flag, double* res) { // передаем флаг по указателю, чтобы его можно было поменять внутри функции
	if ((x < 0) && (b != 0))
		*res = (a * pow(x, 2) + b);

	else if ((x > 0) && (b == 0)) {

		if ((x - c) == 0) {
			*flag = true;
			*res = x;
		}

		else
			*res = ((x - a) / (x - c));
	}

	else {
		if (c == 0) {
			*flag = true;
			*res = x;
		}

		else
			*res = (x / c);
	}
}

double get_number(char var_name) {
	double arg;
	cout << "Введите коэффицент " << var_name << ": ";

	while (!(cin >> arg)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Вы ввели не число!" << endl << "Введите " << var_name << ": ";
	}
	return arg;
}
