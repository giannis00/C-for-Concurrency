#include <stdio.h>
#include <stdlib.h>

#define N 1000000

// returns a new array that the caller must free
double *create_filled(int n, double value)
{
    double *a = malloc(n * sizeof(double));
    if (a == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        a[i] = value;
    }
    return a;
}

int main(void)
{
    double *x = create_filled(N, 1.5);
    double *y = create_filled(N, 2.0);
    if (x == NULL || y == NULL) {
        free(x);                 // free(NULL) is allowed and does nothing
        free(y);
        return 1;
    }

    double dot = 0.0;
    for (int i = 0; i < N; i++) {
        dot += x[i] * y[i];
    }
    printf("Dot product: %.1f\n", dot);

    free(x);
    free(y);
    return 0;
}
