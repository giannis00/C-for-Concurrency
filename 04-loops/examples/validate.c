#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int mark;

    do {
        printf("Mark (0-100): ");
        scanf("%d", &mark);
    } while (mark < 0 || mark > 100);   // note the semicolon

    printf("Accepted: %d\n", mark);
    return 0;
}
