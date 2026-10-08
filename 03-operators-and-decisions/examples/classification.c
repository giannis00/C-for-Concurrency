#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int mark;

    printf("Final mark (0-100): ");
    scanf("%d", &mark);

    if (mark < 0 || mark > 100) {
        printf("That is not a valid mark.\n");
    } else if (mark >= 70) {
        printf("First class\n");
    } else if (mark >= 60) {
        printf("Upper second (2:1)\n");
    } else if (mark >= 50) {
        printf("Lower second (2:2)\n");
    } else if (mark >= 40) {
        printf("Third class\n");
    } else {
        printf("Fail\n");
    }
    return 0;
}
