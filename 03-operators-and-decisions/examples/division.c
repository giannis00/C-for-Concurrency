#include <stdio.h>

int main(void)
{
    int a = 7, b = 2;

    printf("a / b          = %d\n", a / b);            // integer division
    printf("a %% b          = %d\n", a % b);            // remainder
    printf("7.0 / b        = %.1f\n", 7.0 / b);        // one side is a double
    printf("(double) a / b = %.1f\n", (double) a / b); // cast a first

    double wrong = a / b;   // the division is done with integers, then stored
    printf("wrong          = %.1f\n", wrong);
    return 0;
}
