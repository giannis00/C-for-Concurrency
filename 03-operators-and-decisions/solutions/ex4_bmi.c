#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double weight, height;

    printf("Weight (kg) and height (m): ");
    scanf("%lf %lf", &weight, &height);

    double bmi = weight / (height * height);
    printf("BMI: %.1f\n", bmi);

    if (bmi < 18.5) {
        printf("Underweight\n");
    } else if (bmi < 25) {
        printf("Normal weight\n");
    } else if (bmi < 30) {
        printf("Overweight\n");
    } else {
        printf("Obese\n");
    }
    return 0;
}
