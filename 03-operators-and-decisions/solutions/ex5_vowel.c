#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    char letter;

    printf("A lower-case letter: ");
    scanf(" %c", &letter);

    switch (letter) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            printf("'%c' is a vowel.\n", letter);
            break;
        default:
            printf("'%c' is a consonant.\n", letter);
    }
    return 0;
}
