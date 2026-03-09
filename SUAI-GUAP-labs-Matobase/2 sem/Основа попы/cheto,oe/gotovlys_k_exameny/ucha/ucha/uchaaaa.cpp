#include <iostream>
using namespace std;
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}
int add(int a, int b) {
    return a + b;
}
char add(char a, char b) {
    return a + b;
}
int main() {
    setlocale(LC_ALL, "");
    int result1 = add(5, 3); 
    double result2 = add(2.5, 1.8); 
    cout << result1 << "," << result2;
    return 0;
}
