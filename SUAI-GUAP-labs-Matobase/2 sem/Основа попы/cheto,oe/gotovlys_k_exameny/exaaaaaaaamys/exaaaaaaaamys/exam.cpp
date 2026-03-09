#include <iostream>
using namespace std;
int main() {
    int number = 7;

    // Побитовый сдвиг влево
    int shiftedLeft = number << 2;
    std::cout << "Число после побитового сдвига влево: " << shiftedLeft << std::endl;

    // Побитовый сдвиг вправо
    int shiftedRight = number >> 1;
    std::cout << "Число после побитового сдвига вправо: " << shiftedRight << std::endl;

    return 0;
}
