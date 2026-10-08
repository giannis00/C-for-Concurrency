#include <stdio.h>

void fill(int a[], int n, int value)
{
    for (int i = 0; i < n; i++) {
        a[i] = value;
    }
}

void print_array(const int a[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int a[6];

    fill(a, 6, 7);
    print_array(a, 6);
    return 0;
}
