#include <stdio.h>

#define N 5

double sum(const double data[], int n)   // const: this function only reads
{
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

void scale(double data[], int n, double factor)   // this one changes the array
{
    for (int i = 0; i < n; i++) {
        data[i] *= factor;
    }
}

int main(void)
{
    double values[N] = {1.0, 2.0, 3.0, 4.0, 5.0};

    printf("Sum before: %.1f\n", sum(values, N));
    scale(values, N, 10.0);
    printf("Sum after:  %.1f\n", sum(values, N));
    return 0;
}
