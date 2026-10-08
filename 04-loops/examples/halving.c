#include <stdio.h>

int main(void)
{
    int value = 1000;
    int steps = 0;

    while (value > 1) {
        value = value / 2;   // integer division
        steps++;
    }
    printf("1000 can be halved %d times.\n", steps);
    return 0;
}
