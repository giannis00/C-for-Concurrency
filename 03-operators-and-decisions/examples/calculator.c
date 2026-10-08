#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double a, b;
    char op;

    printf("Calculation (for example 3 * 4): ");
    scanf("%lf %c %lf", &a, &op, &b);

    switch (op) {
        case '+':
            printf("%.2f\n", a + b);
            break;
        case '-':
            printf("%.2f\n", a - b);
            break;
        case '*':
            printf("%.2f\n", a * b);
            break;
        case '/':
            if (b == 0) {
                printf("Cannot divide by zero.\n");
            } else {
                printf("%.2f\n", a / b);
            }
            break;
        default:
            printf("Unknown operator '%c'.\n", op);
    }
    return 0;
}
