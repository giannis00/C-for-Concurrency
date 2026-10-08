#include <stdio.h>

#define N 4

int main(void)
{
    double x[N] = {1.0, 2.0, 3.0, 4.0};
    double y[N] = {0.5, 0.25, 2.0, 1.0};
    double dot = 0.0;

    for (int i = 0; i < N; i++) {
        dot += x[i] * y[i];
    }
    printf("Dot product: %.2f\n", dot);
    return 0;
}
