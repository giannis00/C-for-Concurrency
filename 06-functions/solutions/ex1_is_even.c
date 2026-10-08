#include <stdio.h>

int is_even(int n)
{
    return n % 2 == 0;       // a comparison already gives 1 or 0
}

int main(void)
{
    printf("%d %d\n", is_even(4), is_even(7));
    return 0;
}
