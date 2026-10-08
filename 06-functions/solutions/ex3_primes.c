#include <stdio.h>

int is_prime(int n);

int main(void)
{
    for (int n = 2; n < 50; n++) {
        if (is_prime(n)) {
            printf("%d ", n);
        }
    }
    printf("\n");
    return 0;
}

int is_prime(int n)
{
    if (n < 2) {
        return 0;
    }
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return 0;        // a divisor: leave the function at once
        }
    }
    return 1;
}
