// 10to16.cpp : Defines the entry point for the console application.
#include "iostream"
using namespace std;

int main() 
{
	setlocale(LC_ALL, "Russian"); //возможность вывода в консоли русских букв
	int x, y, c;
	unsigned short str=0;
	cout << "Введите число X в диапазоне [0;63]";
	cin >> x;
	cout << "Введите число Y в диапазоне [0;63]";
	cin >> y;
	cout << "Введите число C в диапазоне [0;15]";
	cin >> c;
	if ((x<=63) && (x>=0) && (y <= 63) && (y >= 0) && (c <= 15) && (c >= 0))
	 {   
		str = c;
		str = y << 4 | str;
		str = x << 10 | str;
		cout << "Число str в 10ичной системе = " << str << endl;//вывод получившейся структуры в десятичном системе счисления
		cout << "Число str в 16ричной системе = " << hex << str << endl;//вывод получившейся структуры в шестнадцатеричной системе счисления
	 }	
	else 
	{
      cout << "Введенные числа не соответствуют заданным требованиям!" << endl;
	}
return 0;
}