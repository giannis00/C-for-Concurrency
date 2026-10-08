#include <stdio.h>

int main(void)
{
    int n = 5;

    while (n > 0) {
        printf("%d ", n);
        n--;                 // without this line the loop never ends
    }
    printf("Lift-off!\n");
    return 0;
}
