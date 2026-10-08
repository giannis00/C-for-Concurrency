#include <stdio.h>

#define N 3

int main(void)
{
    int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[N][N] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    int C[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;                         // an accumulator per element
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
