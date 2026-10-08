#include <stdio.h>

int main(void)
{
    const double hours = 2.5;

    printf("%.1f hours = %.0f minutes = %.0f seconds\n",
           hours, hours * 60, hours * 3600);
    return 0;
}
