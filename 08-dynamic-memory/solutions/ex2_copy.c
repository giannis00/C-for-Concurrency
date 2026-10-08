#include <stdio.h>
#include <stdlib.h>

// returns a new array that the caller must free
int *copy_array(const int *source, int n)
{
    int *copy = malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = source[i];
    }
    return copy;
}

int main(void)
{
    int original[4] = {1, 2, 3, 4};

    int *copy = copy_array(original, 4);
    if (copy == NULL) {
        return 1;
    }

    copy[0] = 99;
    printf("original[0] = %d, copy[0] = %d\n", original[0], copy[0]);

    free(copy);
    return 0;
}
