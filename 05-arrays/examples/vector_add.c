#include <stdio.h>

#define N 8

int main(void)
{
    int a[N], b[N], c[N];

    for (int i = 0; i < N; i++) {    // give the inputs some values first
        a[i] = i;
        b[i] = 10 * i;
    }

    for (int i = 0; i < N; i++) {    // the loop that the lab makes parallel
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < N; i++) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }
    return 0;
}
