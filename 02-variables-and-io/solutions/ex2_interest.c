#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double principal, rate, years;

    printf("Principal, rate (%%) and years: ");
    scanf("%lf %lf %lf", &principal, &rate, &years);

    printf("Interest: %.2f\n", principal * rate * years / 100);
    return 0;
}
