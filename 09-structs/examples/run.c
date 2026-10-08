#include <stdio.h>

struct Run {                     // a new type, defined once, above main
    int threads;
    double seconds;
};                               // note the semicolon

int main(void)
{
    struct Run first = {1, 12.4};    // members in the order of the definition
    struct Run second;

    second.threads = 4;              // or member by member
    second.seconds = 3.6;

    printf("%d thread:  %.1f s\n", first.threads, first.seconds);
    printf("%d threads: %.1f s\n", second.threads, second.seconds);
    return 0;
}
