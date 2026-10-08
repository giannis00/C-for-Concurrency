#include <stdio.h>

void add_ten(int x)
{
    x = x + 10;                  // changes the copy only
    printf("inside the function: %d\n", x);
}

int main(void)
{
    int n = 5;

    add_ten(n);
    printf("back in main:        %d\n", n);
    return 0;
}
