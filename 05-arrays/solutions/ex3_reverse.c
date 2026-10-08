#include <stdio.h>

#define N 7

int main(void)
{
    int a[N] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < N / 2; i++) {    // stop in the middle
        int temp = a[i];
        a[i] = a[N - 1 - i];
        a[N - 1 - i] = temp;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
