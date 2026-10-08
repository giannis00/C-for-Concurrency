#include <stdio.h>

int main(void)
{
    double t1 = 12.5, t2 = 6.4, t4 = 3.35;

    printf("%8s %10s\n", "threads", "time (s)");
    printf("%8d %10.3f\n", 1, t1);
    printf("%8d %10.3f\n", 2, t2);
    printf("%8d %10.3f\n", 4, t4);
    return 0;
}
