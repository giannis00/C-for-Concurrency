#include <stdio.h>

#define N 10
#define WORKERS 4

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
    double values[N];
    for (int i = 0; i < N; i++) {
        values[i] = i + 1;
    }

    int chunk = N / WORKERS;         // 2 elements each, 2 left over
    double grand_total = 0.0;

    for (int w = 0; w < WORKERS; w++) {
        int start = w * chunk;
        int count = chunk;
        if (w == WORKERS - 1) {
            count = N - start;       // the last worker takes the rest
        }
        double part = sum(values + start, count);
        printf("Worker %d: elements %d to %d, sum %.0f\n",
               w, start, start + count - 1, part);
        grand_total += part;
    }
    printf("Grand total: %.0f\n", grand_total);
    return 0;
}
