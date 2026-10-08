#include <stdio.h>

typedef struct {
    char name[20];
    int id;
    double mark;
} Student;

#define N 4

void add_bonus(Student *s, double bonus)
{
    s->mark += bonus;
    if (s->mark > 100.0) {
        s->mark = 100.0;
    }
}

int main(void)
{
    Student group[N] = {
        {"Eleni", 101, 67.5},
        {"Nikos", 102, 81.0},
        {"Maria", 103, 74.0},
        {"Petros", 104, 58.5}
    };

    for (int i = 0; i < N; i++) {
        add_bonus(&group[i], 20.0);      // the address of element i
        printf("%-8s %5.1f\n", group[i].name, group[i].mark);
    }
    return 0;
}
