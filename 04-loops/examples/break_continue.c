#include <stdio.h>

int main(void)
{
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            continue;        // skip the multiples of 3
        }
        if (i > 7) {
            break;           // stop the whole loop
        }
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
