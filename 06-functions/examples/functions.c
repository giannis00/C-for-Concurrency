#include <stdio.h>

double average(double a, double b)       // two parameters, returns a double
{
    return (a + b) / 2;
}

void print_line(int length)              // returns nothing
{
    for (int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}

int main(void)
{
    print_line(20);
    printf("Average: %.2f\n", average(3, 4.5));
    print_line(20);
    return 0;
}
