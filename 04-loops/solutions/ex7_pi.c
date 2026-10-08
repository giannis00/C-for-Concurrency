#include <stdio.h>

#define N 1000000

int main(void)
{
    const double width = 1.0 / N;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * width;    // middle of strip i
        sum += 4.0 / (1.0 + x * x);      // height of the curve there
    }
    printf("pi is about %.10f\n", sum * width);
    return 0;
}
