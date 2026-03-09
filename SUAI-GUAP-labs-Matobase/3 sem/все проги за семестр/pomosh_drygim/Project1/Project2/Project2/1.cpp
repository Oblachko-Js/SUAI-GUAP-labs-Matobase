#include <stdio.h>
#include <math.h>
#include <conio.h>

#define m 5
#define n 4

const M_PI = 3.14;

int main() {
    float A[m][n], B[m][n], C[m][n], MaxA, MaxB;
    int i, j;

    printf("Work 8\n\nEnter A[%d][%d]:\n", m, n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%f", &A[i][j]);

    printf("\nArray B[%d][%d]:\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (i > j)
                B[i][j] = cos(i + j);
            else
                B[i][j] = log((2 * M_PI) - j);

            printf("%.3f ", B[i][j]);
        }
        printf("\n");
    }

    MaxA = A[0][0];
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (A[i][j] > MaxA)
                MaxA = A[i][j];

    printf("\nMaxA=%.3f\n", MaxA);

    MaxB = B[0][0];
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (B[i][j] > MaxB)
                MaxB = B[i][j];

    printf("\nMaxB=%.3f\n", MaxB);

    if (MaxA > MaxB)
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                C[i][j] = MaxA * A[i][j];
    else
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                C[i][j] = MaxB * B[i][j];

    printf("\nArray C[%d][%d]:\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%.3f ", C[i][j]);
        printf("\n");
    }

    getch();
    return 0;
}
