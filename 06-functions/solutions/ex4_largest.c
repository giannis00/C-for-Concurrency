#include <stdio.h>

double largest(const double data[], int n)
{
    double best = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > best) {
            best = data[i];
        }
    }
    return best;
}

int main(void)
{
    double values[4] = {2.5, 9.1, 4.0, 7.7};

    printf("Largest: %.1f\n", largest(values, 4));
    return 0;
}
