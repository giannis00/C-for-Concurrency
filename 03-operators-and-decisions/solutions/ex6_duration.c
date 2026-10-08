#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int total;

    printf("Seconds: ");
    scanf("%d", &total);

    int hours   = total / 3600;
    int minutes = (total % 3600) / 60;   // what is left after the full hours
    int seconds = total % 60;

    printf("%d h %d min %d s\n", hours, minutes, seconds);
    return 0;
}
