#include <stdio.h>

#define N 8

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45, 81, 67, 53};
    int total = 0;

    for (int i = 0; i < N; i++) {
        total += marks[i];
    }
    double average = (double) total / N;   // cast, or the decimals are lost

    int above = 0;
    for (int i = 0; i < N; i++) {
        if (marks[i] > average) {
            above++;
        }
    }
    printf("Average: %.1f, above average: %d\n", average, above);
    return 0;
}
