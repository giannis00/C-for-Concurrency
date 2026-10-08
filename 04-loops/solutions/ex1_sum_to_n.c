#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n, total = 0;

    printf("n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        total += i;
    }
    printf("Sum: %d\n", total);
    return 0;
}
