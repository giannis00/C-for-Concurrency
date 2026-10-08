#include <stdio.h>
#include <math.h>                         // announces sqrt, pow, fabs, ...

double hypotenuse(double a, double b);    // prototype: ends with a semicolon

int main(void)
{
    printf("Hypotenuse: %.2f\n", hypotenuse(3.0, 4.0));
    return 0;
}

double hypotenuse(double a, double b)     // the definition can now come later
{
    return sqrt(a * a + b * b);
}
