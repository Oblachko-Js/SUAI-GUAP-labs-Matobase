#include <iostream>
using namespace std;


float valid() {
	float input;
	cin >> input;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << ("Ќеверный формат ввода \n");
		cout << ("¬ведите значение заново \n");
		cin >> input;
	}
	return input;
}

float f(float x, float a, float b, float c, bool* divz) {
	*divz = false;
	float ans = 0;

	if (x < 3 && b != 0)
	{
		ans = a * x * x - b * x + c;
	}
	else if (x > 3 && b == 0)
	{
		if (x - c != 0)
		{
			ans = (x - a) / (x - c);

		}
		else

			*divz = true;
	}
	else
	{
		if (c != 0)
			ans = x / c;
		else
			*divz = true;
	}
	return ans;
}

int main()
{
	setlocale(LC_ALL, "rus");
	float x1, x2, dx, a, b, c;
	bool divz = false;

	cout << "¬ведите a:" << endl;
	a = valid();
	cout << "¬ведите b:" << endl;
	b = valid();
	cout << "¬ведите c:" << endl;
	c = valid();
	cout << "¬ведите начальную точку x:" << endl;
	x1 = valid();
	cout << "¬ведите конечную точку x2:" << endl;
	x2 = valid();
	cout << "¬ведите шаг dx:" << endl;
	dx = valid();
	while (dx <= 0)
	{
		cout << "Ўаг должен быть положительным" << endl;
		dx = valid();
	}


	for (float x = x1; x <= x2; x += dx)
	{

		float res = f(x, a, b, c, &divz);

		if (!divz) {
			cout << "x = " << x << " y = " << res << endl;
		}
		else {
			cout << "x = " << x << " error " << endl;
		}
	}
	return 0;
}
