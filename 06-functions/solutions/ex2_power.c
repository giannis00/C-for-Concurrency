#include <stdio.h>

double power(double base, int exponent)
{
    double result = 1.0;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main(void)
{
    printf("%.1f\n", power(2.0, 10));
    printf("%.3f\n", power(1.5, 3));
    return 0;
}
