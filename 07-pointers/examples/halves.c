#include <stdio.h>

#define N 8

double sum(const double *data, int n)
{
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

int main(void)
{
    double values[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    int half = N / 2;

    double first  = sum(values, half);              // elements 0 to 3
    double second = sum(values + half, N - half);   // elements 4 to 7

    printf("First half:  %.0f\n", first);
    printf("Second half: %.0f\n", second);
    printf("Together:    %.0f\n", first + second);
    return 0;
}
