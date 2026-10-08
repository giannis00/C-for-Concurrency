#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    double x, y;

    printf("Two numbers: ");
    scanf("%lf %lf", &x, &y);

    if (x > y) {
        swap(&x, &y);
    }
    printf("In order: %.2f %.2f\n", x, y);
    return 0;
}
