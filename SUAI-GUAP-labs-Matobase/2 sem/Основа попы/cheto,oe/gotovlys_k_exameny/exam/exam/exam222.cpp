#include <iostream>

int main() {
    int arr[] = { 0, 5, 0, 3, 0, 2, 0 };
    int size = sizeof(arr) / sizeof(arr[0]);

    int countZero = 0;
    int countNonZero = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            countZero++;
        }
        else {
            countNonZero++;
        }
    }

    std::cout << "Number of zeros: " << countZero << std::endl;
    std::cout << "Number of non-zeros: " << countNonZero << std::endl;

    return 0;
}
