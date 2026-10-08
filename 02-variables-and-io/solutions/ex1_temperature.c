#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double celsius;

    printf("Temperature in Celsius: ");
    scanf("%lf", &celsius);

    printf("%.1f C = %.1f F\n", celsius, celsius * 1.8 + 32);
    return 0;
}
