#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int rows;

    printf("Rows: ");
    scanf("%d", &rows);

    for (int row = 1; row <= rows; row++) {
        for (int star = 0; star < row; star++) {   // row number = number of stars
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
