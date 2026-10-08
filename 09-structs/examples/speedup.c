#include <stdio.h>

typedef struct {
    int threads;
    double seconds;
} Run;                           // the type is now called Run

#define RUNS 4

int main(void)
{
    Run runs[RUNS] = {{1, 12.4}, {2, 6.5}, {4, 3.6}, {8, 2.3}};

    printf("%8s %9s %9s\n", "threads", "time (s)", "speed-up");
    for (int i = 0; i < RUNS; i++) {
        double speedup = runs[0].seconds / runs[i].seconds;
        printf("%8d %9.1f %9.2f\n", runs[i].threads, runs[i].seconds, speedup);
    }
    return 0;
}
