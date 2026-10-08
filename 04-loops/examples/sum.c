#include <stdio.h>

#define N 100

int main(void)
{
    int total = 0;               // the accumulator starts empty

    for (int i = 1; i <= N; i++) {
        total += i;              // add one more number in every round
    }
    printf("1 + 2 + ... + %d = %d\n", N, total);
    return 0;
}
