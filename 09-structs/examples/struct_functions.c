#include <stdio.h>

typedef struct {
    int threads;
    double seconds;
} Run;

void print_run(Run r)                        // by value: works on a copy
{
    printf("%d threads, %.1f s\n", r.threads, r.seconds);
}

void set_time(Run *r, double seconds)        // by pointer: changes the original
{
    r->seconds = seconds;
}

double speedup(const Run *base, const Run *other)   // by pointer, read only
{
    return base->seconds / other->seconds;
}

int main(void)
{
    Run one  = {1, 12.4};
    Run four = {4, 0.0};

    set_time(&four, 3.1);
    print_run(four);
    printf("Speed-up: %.1f\n", speedup(&one, &four));
    return 0;
}
