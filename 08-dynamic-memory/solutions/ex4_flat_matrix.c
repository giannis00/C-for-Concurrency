#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rows = 3, cols = 5;

    int *m = malloc(rows * cols * sizeof(int));
    if (m == NULL) {
        return 1;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            m[r * cols + c] = 10 * r + c;    // skip r full rows, then c elements
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%4d", m[r * cols + c]);
        }
        printf("\n");
    }

    free(m);
    return 0;
}
