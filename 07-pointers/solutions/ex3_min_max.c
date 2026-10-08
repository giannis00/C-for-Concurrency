#include <stdio.h>

void min_max(const int a[], int n, int *min, int *max)
{
    *min = a[0];
    *max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < *min) {
            *min = a[i];
        }
        if (a[i] > *max) {
            *max = a[i];
        }
    }
}

int main(void)
{
    int data[5] = {12, 5, 31, 8, 27};
    int lowest, highest;

    min_max(data, 5, &lowest, &highest);
    printf("min = %d, max = %d\n", lowest, highest);
    return 0;
}
