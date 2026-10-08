#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int capacity = 2;            // how many elements fit
    int count = 0;               // how many are in use
    int *list = malloc(capacity * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    for (int value = 10; value <= 70; value += 10) {
        if (count == capacity) {             // full: ask for twice as much
            capacity *= 2;
            int *bigger = realloc(list, capacity * sizeof(int));
            if (bigger == NULL) {
                free(list);
                return 1;
            }
            list = bigger;
            printf("(capacity is now %d)\n", capacity);
        }
        list[count] = value;
        count++;
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}
