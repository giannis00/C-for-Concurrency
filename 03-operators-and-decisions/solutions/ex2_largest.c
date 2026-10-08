#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int a, b, c;

    printf("Three integers: ");
    scanf("%d %d %d", &a, &b, &c);

    int largest = a;          // assume the first, then let the others challenge it
    if (b > largest) {
        largest = b;
    }
    if (c > largest) {
        largest = c;
    }
    printf("Largest: %d\n", largest);
    return 0;
}
