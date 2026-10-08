#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double x, y, z;

    printf("Three numbers: ");
    scanf("%lf %lf %lf", &x, &y, &z);

    printf("Average: %.2f\n", (x + y + z) / 3);
    return 0;
}
