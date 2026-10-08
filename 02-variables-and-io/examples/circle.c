#include <stdio.h>

#define PI 3.14159265358979      // the preprocessor replaces PI by this text

int main(void)
{
    const double radius = 3.0;   // a variable that may not be changed

    printf("Perimeter: %.3f\n", 2 * PI * radius);
    printf("Area:      %.3f\n", PI * radius * radius);
    return 0;
}
