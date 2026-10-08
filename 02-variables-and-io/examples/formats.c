#include <stdio.h>

int main(void)
{
    int    threads = 4;
    double seconds = 2.3456789;

    printf("Threads: %d, time: %f s\n", threads, seconds);
    printf("Rounded: %.2f s\n", seconds);

    // %8d and %8.3f pad on the left so that the columns line up
    printf("%8s %8s\n", "threads", "time");
    printf("%8d %8.3f\n", 1, 9.1);
    printf("%8d %8.3f\n", 16, 0.734);
    return 0;
}
