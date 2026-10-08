#include <stdio.h>

// returns the address of the first negative element, or NULL if there is none
int *first_negative(int *data, int n)
{
    for (int i = 0; i < n; i++) {
        if (data[i] < 0) {
            return &data[i];
        }
    }
    return NULL;
}

int main(void)
{
    int readings[5] = {4, 9, -2, 7, -6};

    int *p = first_negative(readings, 5);
    if (p != NULL) {
        printf("Found %d. Setting it to zero.\n", *p);
        *p = 0;
    }
    printf("Third reading is now %d\n", readings[2]);
    return 0;
}
