#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int threads;
    double seconds;
} Run;

int main(void)
{
    int n;

    printf("How many measurements? ");
    scanf("%d", &n);

    Run *runs = malloc(n * sizeof(Run));
    if (runs == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Threads and seconds: ");
        scanf("%d %lf", &runs[i].threads, &runs[i].seconds);
    }

    printf("%8s %9s %9s\n", "threads", "time (s)", "speed-up");
    for (int i = 0; i < n; i++) {
        printf("%8d %9.1f %9.2f\n", runs[i].threads, runs[i].seconds,
               runs[0].seconds / runs[i].seconds);
    }

    free(runs);
    return 0;
}
