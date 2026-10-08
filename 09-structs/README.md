# 📘 Lesson 09: Structs
### Course: *C for Concurrency*
**Instructor:** Ioannis Tsioulis  
*Part 1: C refresher · Lesson 9 of 9*

[⬅ Course home](../README.md) · [How to run the code](../SETUP.md) · [Online C compiler](https://www.onlinegdb.com/online_c_compiler)

---

## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Define a `struct` type and access its members with the dot operator.
- Shorten type names with `typedef`, and build arrays of structs.
- Pass structs to functions by value and by pointer, and use the arrow operator `->`.
- Combine structs with dynamic memory.
- Describe a piece of work as a struct, the way it is handed to a thread.

> **Prerequisites:** Lessons 01 to 08.
>
> 🔭 **Why this lesson matters later:** when you start a thread yourself with a thread library, you can give it one pointer and nothing more. A struct is how you pack everything the thread needs behind that single pointer.

## 1. Grouping values that belong together

### Intuition first

An array holds many values of the **same** type under one name. A `struct` holds a few values of **different** types under one name, like a form with labelled fields: one measurement of a program has a number of threads (an `int`) and a running time (a `double`).

### Formal definition

A `struct` definition creates a new type. The variables inside it are its **members**. A member is reached with a dot: `variable.member`.

📄 [`examples/run.c`](examples/run.c)

```c
#include <stdio.h>

struct Run {                     // a new type, defined once, above main
    int threads;
    double seconds;
};                               // note the semicolon

int main(void)
{
    struct Run first = {1, 12.4};    // members in the order of the definition
    struct Run second;

    second.threads = 4;              // or member by member
    second.seconds = 3.6;

    printf("%d thread:  %.1f s\n", first.threads, first.seconds);
    printf("%d threads: %.1f s\n", second.threads, second.seconds);
    return 0;
}
```

**Output**

```text
1 thread:  12.4 s
4 threads: 3.6 s
```

A whole struct can be copied with `=`. This is different from arrays, which cannot.

## 2. `typedef` and arrays of structs

Writing `struct Run` everywhere is tiresome. `typedef` gives the type a one-word name.

📄 [`examples/speedup.c`](examples/speedup.c)

```c
#include <stdio.h>

typedef struct {
    int threads;
    double seconds;
} Run;                           // the type is now called Run

#define RUNS 4

int main(void)
{
    Run runs[RUNS] = {{1, 12.4}, {2, 6.5}, {4, 3.6}, {8, 2.3}};

    printf("%8s %9s %9s\n", "threads", "time (s)", "speed-up");
    for (int i = 0; i < RUNS; i++) {
        double speedup = runs[0].seconds / runs[i].seconds;
        printf("%8d %9.1f %9.2f\n", runs[i].threads, runs[i].seconds, speedup);
    }
    return 0;
}
```

**Output**

```text
 threads  time (s)  speed-up
       1      12.4      1.00
       2       6.5      1.91
       4       3.6      3.44
       8       2.3      5.39
```

`runs[i].seconds` reads from left to right: the array `runs`, its element `i`, the member `seconds` of that element. The **speed-up** in the last column is the time with one thread divided by the time with several: it says how many times faster the program became. The times in this table are invented for the example.

## 3. Structs and functions

### Intuition first

A struct argument is passed by value like any other: the function gets a copy of the whole form. To let the function change the original, or to avoid copying a large struct, pass its address. For a pointer `p` to a struct, the member is written `p->member`.

| You have | You write | Meaning |
| --- | --- | --- |
| a struct `r` | `r.seconds` | the member of `r` |
| a pointer `p` to a struct | `p->seconds` | the member of the struct that `p` points at |
| | `(*p).seconds` | the same, written the long way |

📄 [`examples/struct_functions.c`](examples/struct_functions.c)

```c
#include <stdio.h>

typedef struct {
    int threads;
    double seconds;
} Run;

void print_run(Run r)                        // by value: works on a copy
{
    printf("%d threads, %.1f s\n", r.threads, r.seconds);
}

void set_time(Run *r, double seconds)        // by pointer: changes the original
{
    r->seconds = seconds;
}

double speedup(const Run *base, const Run *other)   // by pointer, read only
{
    return base->seconds / other->seconds;
}

int main(void)
{
    Run one  = {1, 12.4};
    Run four = {4, 0.0};

    set_time(&four, 3.1);
    print_run(four);
    printf("Speed-up: %.1f\n", speedup(&one, &four));
    return 0;
}
```

**Output**

```text
4 threads, 3.1 s
Speed-up: 4.0
```

## 4. Structs and dynamic memory

A pointer from `malloc` does not know how many elements it points at (Lesson 06, Lesson 07). A struct can keep the two together, so that they travel as one value.

📄 [`examples/vector.c`](examples/vector.c)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *data;                // a block on the heap
    int size;                    // how many elements the block has
} Vector;

// returns a zero-filled vector; data is NULL if the allocation failed
Vector vector_create(int size)
{
    Vector v;
    v.data = calloc(size, sizeof(double));
    v.size = (v.data != NULL) ? size : 0;
    return v;
}

void vector_free(Vector *v)
{
    free(v->data);
    v->data = NULL;              // the vector no longer owns a block
    v->size = 0;
}

double vector_sum(const Vector *v)
{
    double total = 0.0;
    for (int i = 0; i < v->size; i++) {
        total += v->data[i];
    }
    return total;
}

int main(void)
{
    Vector v = vector_create(5);
    if (v.data == NULL) {
        return 1;
    }

    for (int i = 0; i < v.size; i++) {
        v.data[i] = 1.5 * i;
    }
    printf("%d elements, sum %.1f\n", v.size, vector_sum(&v));

    vector_free(&v);
    return 0;
}
```

**Output**

```text
5 elements, sum 15.0
```

`vector_sum` needs one argument instead of two, and it cannot be given the wrong length by mistake.

> ⚠️ **Common pitfalls**
>
> - **Forgetting the semicolon** after the closing brace of a struct definition. The error message appears on the following line.
> - **A dot where an arrow is needed.** With a pointer `p`, write `p->size`. `p.size` does not compile.
> - **Copying a struct that contains a pointer.** `Vector b = a;` copies the address, not the block. `a` and `b` then share the same elements, and freeing both is a double free.
> - **Comparing structs with `==`.** It does not compile. Compare the members one by one.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

int main(void)
{
    Point a = {1, 2};
    Point b = a;

    b.x = 10;
    printf("%d %d\n", a.x, b.x);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
1 10
```

`Point b = a;` copies all the members. From then on `a` and `b` are separate variables.

</details>

**Q2.** What does this program print?

```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void move_copy(Point p)
{
    p.x = p.x + 5;
}

void move_original(Point *p)
{
    p->x = p->x + 5;
}

int main(void)
{
    Point a = {1, 2};

    move_copy(a);
    printf("%d ", a.x);
    move_original(&a);
    printf("%d\n", a.x);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
1 6
```

`move_copy` changes its own copy, which is thrown away. `move_original` receives the address and changes `a` itself.

</details>

**Q3.** `p` is a pointer to a `Run`. Write `p->threads` without the arrow. Why are the brackets needed?

<details><summary>💡 Show answer</summary>

`(*p).threads`. Without brackets, `*p.threads` would be read as `*(p.threads)`, because the dot is applied before the star. The arrow exists to avoid this.

</details>

**Q4.** What is wrong here?

```c
Run *r;
r->threads = 4;
```

<details><summary>💡 Show answer</summary>

`r` is an uninitialised pointer: there is no `Run` for it to point at. Either declare a variable, `Run run; Run *r = &run;`, or allocate one with `malloc(sizeof(Run))`.

</details>

**Q5.** A function is declared `void report(Vector v)`. Does calling it copy the elements of the vector?

<details><summary>💡 Show answer</summary>

No. It copies the struct, that is, one address and one `int`. The copy points at the same block of elements. The call is cheap, but the function could change the caller's elements through its copy.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (distance)

Define a type `Point` with `double` members `x` and `y`, and write `double distance(Point a, Point b)`. Print the distance between (0, 0) and (3, 4). The square root function `sqrt` is in `math.h`.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex1_distance.c`](solutions/ex1_distance.c)

```c
#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double distance(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
    Point origin = {0.0, 0.0};
    Point p = {3.0, 4.0};

    printf("Distance: %.1f\n", distance(origin, p));
    return 0;
}
```

</details>

### Exercise 2 (best student)

Define a type `Student` with a name (a `char` array of 20), an id and a mark. Create an array of four students and print the name and the mark of the one with the highest mark.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex2_best_student.c`](solutions/ex2_best_student.c)

```c
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
```

</details>

### Exercise 3 (bonus marks)

For the same `Student` type, write `void add_bonus(Student *s, double bonus)` that raises the mark of one student, but never above 100. Give every student of the group 20 bonus points and print the new marks.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex3_bonus.c`](solutions/ex3_bonus.c)

```c
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
```

*`%-8s` pads the name on the right, so the marks line up.*

</details>

### Exercise 4 (your own measurements)

Use the `Run` type of this lesson. Ask how many measurements there are, allocate an array of that many `Run` values with `malloc`, read the number of threads and the time of each one, and print the table with the speed-up column as in section 2. The first measurement is the reference.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex4_measurements.c`](solutions/ex4_measurements.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int threads;
    double seconds;
} Run;

int main(void)
{
    int n;

    printf("How many measurements? ");
    scanf("%d", &n);

    Run *runs = malloc(n * sizeof(Run));
    if (runs == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Threads and seconds: ");
        scanf("%d %lf", &runs[i].threads, &runs[i].seconds);
    }

    printf("%8s %9s %9s\n", "threads", "time (s)", "speed-up");
    for (int i = 0; i < n; i++) {
        printf("%8d %9.1f %9.2f\n", runs[i].threads, runs[i].seconds,
               runs[0].seconds / runs[i].seconds);
    }

    free(runs);
    return 0;
}
```

</details>

### Exercise 5 (more vector functions)

Start from `vector.c` in the examples folder. Add `void vector_fill(Vector *v, double value)` and `double vector_dot(const Vector *a, const Vector *b)`. `vector_dot` returns 0 when the sizes differ. Test with two vectors of 4 elements filled with 3.0 and 0.5.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex5_vector_functions.c`](solutions/ex5_vector_functions.c)

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *data;
    int size;
} Vector;

Vector vector_create(int size)
{
    Vector v;
    v.data = calloc(size, sizeof(double));
    v.size = (v.data != NULL) ? size : 0;
    return v;
}

void vector_free(Vector *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
}

void vector_fill(Vector *v, double value)
{
    for (int i = 0; i < v->size; i++) {
        v->data[i] = value;
    }
}

double vector_dot(const Vector *a, const Vector *b)
{
    if (a->size != b->size) {
        return 0.0;
    }
    double dot = 0.0;
    for (int i = 0; i < a->size; i++) {
        dot += a->data[i] * b->data[i];
    }
    return dot;
}

int main(void)
{
    Vector a = vector_create(4);
    Vector b = vector_create(4);
    if (a.data == NULL || b.data == NULL) {
        vector_free(&a);
        vector_free(&b);
        return 1;
    }

    vector_fill(&a, 3.0);
    vector_fill(&b, 0.5);
    printf("Dot product: %.1f\n", vector_dot(&a, &b));

    vector_free(&a);
    vector_free(&b);
    return 0;
}
```

</details>

### Exercise 6 (a job description for each worker, a little harder)

In Lesson 07, Exercise 5, four workers each added up a part of an array. Describe the job of one worker as a struct:

```c
typedef struct {
    const double *data;   // where this worker's part begins
    int count;            // how many elements it has
    double result;        // filled in by the worker
} Task;
```

Write `void run_task(Task *t)` that adds up the part and stores the sum in `t->result`. In `main`, fill an array of 10 elements with 1 to 10, prepare an array of four `Task` values, run them one after another, and add the four results.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex6_tasks.c`](solutions/ex6_tasks.c)

```c
#include <stdio.h>

#define N 10
#define WORKERS 4

typedef struct {
    const double *data;   // where this worker's part begins
    int count;            // how many elements it has
    double result;        // filled in by the worker
} Task;

void run_task(Task *t)
{
    t->result = 0.0;
    for (int i = 0; i < t->count; i++) {
        t->result += t->data[i];
    }
}

int main(void)
{
    double values[N];
    for (int i = 0; i < N; i++) {
        values[i] = i + 1;
    }

    Task tasks[WORKERS];
    int chunk = N / WORKERS;

    for (int w = 0; w < WORKERS; w++) {          // 1. describe the jobs
        int start = w * chunk;
        tasks[w].data  = values + start;
        tasks[w].count = (w == WORKERS - 1) ? N - start : chunk;
    }

    for (int w = 0; w < WORKERS; w++) {          // 2. do the jobs
        run_task(&tasks[w]);
    }

    double total = 0.0;
    for (int w = 0; w < WORKERS; w++) {          // 3. collect the results
        printf("Worker %d: %d elements, sum %.0f\n",
               w, tasks[w].count, tasks[w].result);
        total += tasks[w].result;
    }
    printf("Total: %.0f\n", total);
    return 0;
}
```

**Output**

```text
Worker 0: 2 elements, sum 3
Worker 1: 2 elements, sum 7
Worker 2: 2 elements, sum 11
Worker 3: 4 elements, sum 34
Total: 55
```

*Describe, do, collect. In step 2 the four calls do not touch each other's data: each one reads its own part of the array and writes its own `result`. That is what would allow them to run at the same time, each in its own thread.*

</details>

---

## 🔑 Key takeaways

- A **`struct`** groups members of different types into one new type; **`typedef`** gives it a short name.
- Members are reached with **`.`** from a struct and with **`->`** from a pointer to a struct.
- Structs are **copied** on assignment and when passed by value; pass a **pointer** to change the original.
- A struct that holds a **pointer and a size** keeps a dynamic array and its length together.
- Copying a struct copies the **pointer inside it**, not the block it points at.
- A struct is the usual way to hand **a complete job description** to a function or a thread.


---

🏁 **You have completed the C refresher.** You can now read and write the C that the parallel programming labs are built on: loops over arrays, functions that take pointers, and memory that you allocate and free yourself. Go back to the [course home](../README.md) to see what comes next.

*© Ioannis Tsioulis. *C for Concurrency*. Prepared for educational use.*
