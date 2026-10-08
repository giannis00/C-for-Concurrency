#include <stdio.h>

int count_char(const char *text, char wanted)
{
    int count = 0;

    while (*text != '\0') {      // text is a copy of the address: moving it is safe
        if (*text == wanted) {
            count++;
        }
        text++;
    }
    return count;
}

int main(void)
{
    printf("%d\n", count_char("concurrency and communication", 'c'));
    return 0;
}
