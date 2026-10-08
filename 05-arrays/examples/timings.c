#include <stdio.h>

#define RUNS 6

int main(void)
{
    // the same program, timed six times (seconds)
    double times[RUNS] = {2.31, 2.28, 2.45, 2.27, 2.36, 2.30};

    double total = 0.0;
    double best = times[0];          // assume the first is the fastest

    for (int i = 0; i < RUNS; i++) {
        total += times[i];
        if (times[i] < best) {
            best = times[i];
        }
    }

    printf("Average: %.3f s\n", total / RUNS);
    printf("Best:    %.3f s\n", best);
    return 0;
}
