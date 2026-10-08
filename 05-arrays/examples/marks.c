#include <stdio.h>

#define N 5

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45};

    marks[1] = 61;       // change the second element

    printf("First: %d, last: %d\n", marks[0], marks[N - 1]);

    for (int i = 0; i < N; i++) {
        printf("marks[%d] = %d\n", i, marks[i]);
    }
    return 0;
}
