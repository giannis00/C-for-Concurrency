#include <stdio.h>

typedef struct {
    char name[20];
    int id;
    double mark;
} Student;

#define N 4

int main(void)
{
    Student group[N] = {
        {"Eleni", 101, 67.5},
        {"Nikos", 102, 81.0},
        {"Maria", 103, 74.0},
        {"Petros", 104, 58.5}
    };
    int best = 0;                        // index of the best so far

    for (int i = 1; i < N; i++) {
        if (group[i].mark > group[best].mark) {
            best = i;
        }
    }
    printf("%s with %.1f\n", group[best].name, group[best].mark);
    return 0;
}
