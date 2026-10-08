#include <stdio.h>

int main(void)
{
    int    x = 42;
    double y = 1.5;

    printf("x holds %d and lives at %p\n", x, (void *) &x);
    printf("y holds %.1f and lives at %p\n", y, (void *) &y);
    return 0;
}
