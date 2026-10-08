#define _CRT_SECURE_NO_WARNINGS   // lets scanf build in Visual Studio
#include <stdio.h>

int main(void)
{
    int year;

    printf("What year were you born? ");
    scanf("%d", &year);

    printf("In 2026 you turn %d.\n", 2026 - year);
    return 0;
}
