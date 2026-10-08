#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;
    long long factorial = 1;     // a product starts at 1, not at 0

    printf("n (0-20): ");
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        factorial *= i;
    }
    printf("%d! = %lld\n", n, factorial);
    return 0;
}
