#include <stdio.h>

void swap(int *a, int *b)        // a and b are addresses
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    int x = 3, y = 8;

    swap(&x, &y);                // hand over where x and y live
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
