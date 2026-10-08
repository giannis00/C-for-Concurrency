#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>              // malloc and free

int main(void)
{
    int n;

    printf("How many squares? ");
    scanf("%d", &n);

    int *squares = malloc(n * sizeof(int));    // room for n ints
    if (squares == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        squares[i] = i * i;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    free(squares);               // give the block back
    return 0;
}
