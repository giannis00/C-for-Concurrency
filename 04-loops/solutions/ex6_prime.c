#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;
    int is_prime = 1;            // assume prime until a divisor is found

    printf("An integer above 1: ");
    scanf("%d", &n);

    for (int d = 2; d * d <= n; d++) {   // no need to go beyond the square root
        if (n % d == 0) {
            is_prime = 0;
            break;
        }
    }

    if (is_prime) {
        printf("%d is prime.\n", n);
    } else {
        printf("%d is not prime.\n", n);
    }
    return 0;
}
