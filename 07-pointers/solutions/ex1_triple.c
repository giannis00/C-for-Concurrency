#include <stdio.h>

void triple(int *n)
{
    *n = *n * 3;
}

int main(void)
{
    int value = 7;

    triple(&value);
    printf("%d\n", value);
    return 0;
}
