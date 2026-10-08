#define _CRT_SECURE_NO_WARNINGS   // lets scanf build in Visual Studio
#include <stdio.h>

int main(void)
{
    double width, height;

    printf("Width and height: ");
    scanf("%lf %lf", &width, &height);

    printf("Area: %.2f\n", width * height);
    return 0;
}
