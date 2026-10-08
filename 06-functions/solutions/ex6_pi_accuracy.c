#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double approximate_pi(int steps)
{
    const double width = 1.0 / steps;
    double sum = 0.0;

    for (int i = 0; i < steps; i++) {
        double x = (i + 0.5) * width;
        sum += 4.0 / (1.0 + x * x);
    }
    return sum * width;
}

int main(void)
{
    printf("%8s %14s %10s\n", "steps", "result", "error");
    for (int steps = 10; steps <= 10000; steps *= 10) {
        double result = approximate_pi(steps);
        printf("%8d %14.10f %10.2e\n", steps, result, fabs(result - PI));
    }
    return 0;
}
