#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n, digits = 0;

    printf("A positive integer: ");
    scanf("%d", &n);

    while (n > 0) {
        n /= 10;        // integer division removes the last digit
        digits++;
    }
    printf("Digits: %d\n", digits);
    return 0;
}
