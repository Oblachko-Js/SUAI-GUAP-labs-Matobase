#include <iostream>
using namespace std;

bool check(double x, double y);
double get_number(char var_name);

int main() {
	bool res;

	double x = get_number('x');
	double y = get_number('y');

	res = check(x, y);
	if (res)
		cout << "True" << endl;
	else
		cout << "False" << endl;


	return 0;
}


bool check(double x, double y) {
	bool flag = false;
	if ((((x * x + y * y) <= 1) && (y >= 0)) || (((y <= 0) && (y >= -1)) && ((x >= -1) && (x <= 1))))
		flag = true;
	return flag;
}


double get_number(char var_name) {
	double arg;
	cout << "Enter " << var_name << ": ";

	while (!(cin >> arg)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You entered not a number!\n" << "Enter " << var_name << ": ";
	}
	return arg;
}
