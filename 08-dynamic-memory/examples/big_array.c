#include <stdio.h>
#include <stdlib.h>

#define N 5000000                // five million elements

int main(void)
{
    double *data = malloc(N * sizeof(double));
    if (data == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }
    printf("Allocated %.0f MB\n", N * sizeof(double) / (1024.0 * 1024.0));

    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    double total = 0.0;
    for (int i = 0; i < N; i++) {
        total += data[i];
    }
    printf("Sum: %.0f\n", total);

    free(data);
    return 0;
}
