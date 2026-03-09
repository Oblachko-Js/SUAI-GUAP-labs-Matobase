#include <iostream>

int Sum_numbers(int a, int b, int& c)
{
	c = a + b;
	return c;
}

int main()
{
	int a, b, c = 0;
	std::cout << "Write number a = ";
	std::cin >> a;
	std::cout << "Write number b = ";
	std::cin >> b;
	Sum_numbers(a, b, c);
	std::cout << "Sum c = " << c << '\n';
}