#include <iostream>
using namespace std;

int main() {
    int s;

    cout << "Enter a number in hexadecimal notation: ";
    cin >> hex >> s;

    while (cin.fail() || ((s >> 11) & 0x1) != 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Input number is out of range [0000:F7FF]" << endl;
        cin >> s;
    }

    int n = s >> 12;
    int p = s >> 8 & 7;
    int u = s & 255;

    cout << dec << n << ' ' << 0 << ' ' << p << ' ' << u << endl;
    return 0;
}
