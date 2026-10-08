#include <stdio.h>

int main(void)
{
    for (int row = 1; row <= 4; row++) {
        for (int col = 1; col <= 6; col++) {
            printf("%4d", row * col);
        }
        printf("\n");        // end of the row
    }
    return 0;
}
