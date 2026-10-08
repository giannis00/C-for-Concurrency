#include <stdio.h>

int sum(const int *start, int n)
{
    int total = 0;

    for (const int *p = start; p < start + n; p++) {   // p visits each element
        total += *p;
    }
    return total;
}

int main(void)
{
    int data[6] = {1, 2, 3, 4, 5, 6};

    printf("%d\n", sum(data, 6));
    return 0;
}
