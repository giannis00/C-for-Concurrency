#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void)
{
    int grid[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (int r = 0; r < ROWS; r++) {
        int row_total = 0;
        for (int c = 0; c < COLS; c++) {
            printf("%4d", grid[r][c]);
            row_total += grid[r][c];
        }
        printf("   | row total %d\n", row_total);
    }
    return 0;
}
