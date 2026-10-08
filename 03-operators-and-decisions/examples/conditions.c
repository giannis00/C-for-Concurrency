#include <stdio.h>

int main(void)
{
    int age = 20;

    printf("%d\n", age >= 18);               // true is 1
    printf("%d\n", age == 21);               // false is 0
    printf("%d\n", age >= 18 && age < 65);   // both parts are true
    printf("%d\n", age < 18 || age >= 65);   // neither part is true
    printf("%d\n", !(age == 21));            // not false
    return 0;
}
