#include <stdio.h>

int main(void)
{
    int v[5] = {10, 20, 30, 40, 50};
    int *p = v;                      // same as &v[0]

    printf("%d %d %d\n", v[2], p[2], *(p + 2));   // three ways to say v[2]

    p = p + 3;                       // p now points at v[3]
    printf("%d %d\n", *p, p[1]);     // v[3] and the element after it
    return 0;
}
