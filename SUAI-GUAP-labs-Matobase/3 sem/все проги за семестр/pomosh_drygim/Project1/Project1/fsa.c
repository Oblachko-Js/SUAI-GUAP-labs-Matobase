#include <stdio.h>
#include <math.h>
#include <conio.h>

int main() {
    float a = 1.5, b = 2.6, c = -0.4, p0 = 1.5, h = 0.2;
    int n = 6, m = 5;
    float x = a > b ? (a > c ? a : c) : (b > c ? b : c);

    printf("x = %.4f\n", x);

    for (int i = 1; i <= m; i++) {
        float p = p0 + (i - 1) * h;
        float term = 0.0;
        float sum = 0.0;

        for (int k = 0; k <= n; k++) {
            term = pow(-1, k + 1) * pow(p, k) * pow(sin(x), k) / (k + 1);
            sum += term;
        }

        printf("Сумма ряда для p = %.4f: %.4f\n", p, sum);
    }

    getch(); // Ожидаем нажатия клавиши перед закрытием окна

    return 0;
}
