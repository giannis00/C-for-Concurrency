#include <stdio.h>

int main(void)
{
    int x = 42;
    int *p = &x;             // p points at x

    printf("x = %d, *p = %d\n", x, *p);

    *p = 100;                // write through the pointer
    printf("x = %d\n", x);

    x = 7;                   // change x directly
    printf("*p = %d\n", *p);
    return 0;
}
