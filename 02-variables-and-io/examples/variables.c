#include <stdio.h>

int main(void)
{
    int    students = 24;       // whole number
    double average  = 61.5;     // real number
    float  ratio    = 0.75f;    // real number with less precision
    char   grade    = 'B';      // one character, in single quotes

    students = students + 1;    // a variable can change its value

    printf("Students: %d\n", students);
    printf("Average:  %.1f\n", average);
    printf("Ratio:    %.2f\n", ratio);
    printf("Grade:    %c\n", grade);
    return 0;
}
