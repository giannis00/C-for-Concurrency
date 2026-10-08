#include <stdio.h>

int calls = 0;                   // global: one variable for the whole program

void work(void)
{
    int steps = 0;               // local: created again at every call

    steps++;
    calls++;
    printf("steps = %d, calls = %d\n", steps, calls);
}

int main(void)
{
    work();
    work();
    work();
    return 0;
}
