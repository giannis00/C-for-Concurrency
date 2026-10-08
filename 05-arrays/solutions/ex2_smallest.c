#include <stdio.h>

#define N 8

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45, 81, 67, 53};
    int where = 0;                   // index of the smallest so far

    for (int i = 1; i < N; i++) {
        if (marks[i] < marks[where]) {
            where = i;
        }
    }
    printf("Smallest: %d at index %d\n", marks[where], where);
    return 0;
}
