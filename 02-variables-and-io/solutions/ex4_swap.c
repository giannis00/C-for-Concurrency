#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int a, b;

    printf("Two integers: ");
    scanf("%d %d", &a, &b);

    int temp = a;   // keep the old a before it is overwritten
    a = b;
    b = temp;

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
