#include <stdio.h>
#include <stdlib.h>

// returns a new array: start, start + step, start + 2 * step, ...
// the caller must free it
double *make_ramp(int n, double start, double step)
{
    double *ramp = malloc(n * sizeof(double));
    if (ramp == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        ramp[i] = start + i * step;
    }
    return ramp;
}

int main(void)
{
    double *x = make_ramp(5, 0.0, 0.25);
    if (x == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%.2f ", x[i]);
    }
    printf("\n");

    free(x);                     // allocated in make_ramp, freed here
    return 0;
}
