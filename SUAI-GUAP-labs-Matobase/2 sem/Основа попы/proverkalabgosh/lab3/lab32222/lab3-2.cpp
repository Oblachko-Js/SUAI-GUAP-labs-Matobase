#include <iostream>
#include <string>
using namespace std;

int get_number(string var, string interval, int max_value);

int main() {
	int n, o = 0, p, u;

	n = get_number("N", "[0, 15]", 15);
	p = get_number("P", "[0, 7]", 7);
	u = get_number("U", "[0, 255]", 255);

	unsigned short s = u | p << 8 | o << 11 | n << 12;
	cout << "\n Packed structure:" << hex << s << endl;
}


int get_number(string var, string interval, int max_value) {
	int arg;
	string message = "Enter a number(" + var + ") from the interval" + interval + ": ";
	cout << message;


	while (!(cin >> arg) || (arg < 0) || (arg > max_value)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You entered not required Number!\n" << message;
	}

	return arg;
}
