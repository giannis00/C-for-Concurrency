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

    for (int c = 0; c < COLS; c++) {         // now the columns are the outer loop
        int total = 0;
        for (int r = 0; r < ROWS; r++) {
            total += grid[r][c];
        }
        printf("Column %d: %d\n", c, total);
    }
    return 0;
}
