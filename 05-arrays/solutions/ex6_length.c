#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    char word[20];
    int length = 0;

    printf("A word: ");
    scanf("%19s", word);

    while (word[length] != '\0') {   // count until the end marker
        length++;
    }
    printf("Length: %d\n", length);
    return 0;
}
