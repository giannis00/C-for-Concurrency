#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;

    printf("How many marks? ");
    scanf("%d", &n);

    double *marks = malloc(n * sizeof(double));
    if (marks == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter the marks: ");
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &marks[i]);     // the address of element i
        total += marks[i];
    }
    printf("Average: %.1f\n", total / n);

    free(marks);
    return 0;
}
