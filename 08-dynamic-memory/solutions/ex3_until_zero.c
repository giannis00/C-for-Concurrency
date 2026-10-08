#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int capacity = 2, count = 0;
    int *numbers = malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    int value;
    printf("Number (0 to stop): ");
    scanf("%d", &value);

    while (value != 0) {
        if (count == capacity) {
            capacity *= 2;
            int *bigger = realloc(numbers, capacity * sizeof(int));
            if (bigger == NULL) {
                free(numbers);
                return 1;
            }
            numbers = bigger;
        }
        numbers[count] = value;
        count++;

        printf("Number (0 to stop): ");
        scanf("%d", &value);
    }

    printf("In reverse:");
    for (int i = count - 1; i >= 0; i--) {
        printf(" %d", numbers[i]);
    }
    printf("\n");

    free(numbers);
    return 0;
}
