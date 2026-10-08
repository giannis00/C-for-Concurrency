#include <stdio.h>
#include <string.h>     // for strlen

int main(void)
{
    char name[] = "Ada";     // four elements: 'A' 'd' 'a' '\0'

    printf("%s has %zu letters and takes %zu bytes.\n",
           name, strlen(name), sizeof(name));

    name[0] = 'I';           // a string is an array: elements can be changed
    printf("Now it says %s.\n", name);

    for (int i = 0; name[i] != '\0'; i++) {   // walk until the end marker
        printf("[%c]", name[i]);
    }
    printf("\n");
    return 0;
}
