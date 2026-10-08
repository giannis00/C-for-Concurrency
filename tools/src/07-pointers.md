## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Explain what an address is and obtain one with `&`.
- Declare a pointer, make it point at a variable, and read or write through it with `*`.
- Write functions that change their caller's variables, and functions that give back more than one result.
- Describe the relation between arrays and pointers, and pass part of an array to a function.
- Recognise the three kinds of invalid pointer: uninitialised, `NULL` and dangling.

> **Prerequisites:** Lessons 01 to 06, in particular "pass by value" in Lesson 06.
>
> 🔭 **Why this lesson matters later:** threads and processes are handed their share of the work as "a pointer to where your part begins, and how many elements it has". MPI functions take the address of the data to send or receive.

## 1. Every variable has an address

### Intuition first

Memory is a very long street of numbered houses, one byte each. A variable occupies a few neighbouring houses. Its **address** is the number of the first one. The name `x` gives you what is inside; `&x` gives you where it is.

```c file=examples/address.c
#include <stdio.h>

int main(void)
{
    int    x = 42;
    double y = 1.5;

    printf("x holds %d and lives at %p\n", x, (void *) &x);
    printf("y holds %.1f and lives at %p\n", y, (void *) &y);
    return 0;
}
```

@@output

The addresses are printed in hexadecimal, and they will be different on your computer and from one run to the next. Their exact values never matter. What matters is that they can be stored and passed around.

## 2. Pointer variables

### Formal definition

A **pointer** is a variable whose value is an address. Its type says what kind of variable lives at that address.

| Code | Meaning |
| --- | --- |
| `int *p;` | `p` is a pointer to an `int` |
| `p = &x;` | `p` now holds the address of `x`: "`p` points at `x`" |
| `*p` | the variable that `p` points at (**dereferencing**) |

```text
       p                    x
  +---------+          +---------+
  | address |  ----->  |   42    |
  +---------+          +---------+
```

```c file=examples/pointer.c
#include <stdio.h>

int main(void)
{
    int x = 42;
    int *p = &x;             // p points at x

    printf("x = %d, *p = %d\n", x, *p);

    *p = 100;                // write through the pointer
    printf("x = %d\n", x);

    x = 7;                   // change x directly
    printf("*p = %d\n", *p);
    return 0;
}
```

@@output

`x` and `*p` are two names for the same piece of memory. Note the two roles of the star: in a declaration (`int *p`) it says "this is a pointer"; in an expression (`*p = 100`) it says "go to the address".

## 3. Pointers as function parameters

### Intuition first

Lesson 06 ended with a problem: a function receives copies, so it cannot change the variables of its caller. The way out is to pass the **address** of a variable. The address is still copied, but a copy of an address leads to the same house.

```c file=examples/swap.c
#include <stdio.h>

void swap(int *a, int *b)        // a and b are addresses
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    int x = 3, y = 8;

    swap(&x, &y);                // hand over where x and y live
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
```

@@output

This is what `scanf("%d", &n)` has been doing since Lesson 02: it receives the address of `n` so that it can store a value there.

### More than one result

A function has one return value. With pointer parameters it can deliver as many results as it likes.

```c file=examples/divide.c
#include <stdio.h>

void divide(int a, int b, int *quotient, int *remainder)
{
    *quotient  = a / b;
    *remainder = a % b;
}

int main(void)
{
    int q, r;

    divide(17, 5, &q, &r);
    printf("17 = 5 * %d + %d\n", q, r);
    return 0;
}
```

@@output

## 4. Pointers and arrays

### Formal definition

The name of an array, used in an expression, gives the address of its first element: `v` means the same as `&v[0]`. Adding an integer to a pointer moves it by that many **elements**, not bytes. Therefore:

| Expression | Means |
| --- | --- |
| `p = v;` | `p` points at `v[0]` |
| `p + 2` | the address of `v[2]` |
| `*(p + 2)` | `v[2]` |
| `p[2]` | also `v[2]`: the square brackets work on any pointer |

```c file=examples/pointer_array.c
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
```

@@output

This explains Lesson 06: a parameter written `double data[]` is really a pointer, `double *data`. The function receives the address of the first element, which is why it can change the caller's array and why it cannot know the length.

### Why it matters

Since a function only needs "where to start" and "how many", you can hand it **any part** of an array.

```c file=examples/halves.c
#include <stdio.h>

#define N 8

double sum(const double *data, int n)
{
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

int main(void)
{
    double values[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    int half = N / 2;

    double first  = sum(values, half);              // elements 0 to 3
    double second = sum(values + half, N - half);   // elements 4 to 7

    printf("First half:  %.0f\n", first);
    printf("Second half: %.0f\n", second);
    printf("Together:    %.0f\n", first + second);
    return 0;
}
```

@@output

Two workers could compute the two halves at the same time, each with its own `total`, and the results would be added at the end. Much of parallel programming follows this plan.

## 5. Pointers that point nowhere

A pointer is only useful while it holds the address of something that exists.

| Kind | How it happens | What to do |
| --- | --- | --- |
| **Uninitialised** | `int *p;` and then `*p = 5;` | give every pointer a value when you declare it |
| **Null** | the pointer was set to `NULL`, meaning "points at nothing" | test `if (p != NULL)` before using `*p` |
| **Dangling** | it holds the address of a variable that no longer exists | never return the address of a local variable |

`NULL` is useful as an answer: a function that searches for something can return `NULL` for "not found".

```c file=examples/null.c
#include <stdio.h>

// returns the address of the first negative element, or NULL if there is none
int *first_negative(int *data, int n)
{
    for (int i = 0; i < n; i++) {
        if (data[i] < 0) {
            return &data[i];
        }
    }
    return NULL;
}

int main(void)
{
    int readings[5] = {4, 9, -2, 7, -6};

    int *p = first_negative(readings, 5);
    if (p != NULL) {
        printf("Found %d. Setting it to zero.\n", *p);
        *p = 0;
    }
    printf("Third reading is now %d\n", readings[2]);
    return 0;
}
```

@@output

> ⚠️ **Common pitfalls**
>
> - **Using `*p` before `p` points anywhere.** The pointer holds a random address. Writing there damages other data or crashes the program ("segmentation fault", "access violation").
> - **Returning the address of a local variable.** The variable disappears when the function returns, and the caller is left with a dangling pointer.
> - **Declaring two pointers on one line.** `int *p, q;` makes `p` a pointer and `q` a plain `int`. Write one declaration per line.
> - **Forgetting the `&` in a call.** `swap(x, y)` passes the *values* 3 and 8 as if they were addresses. The compiler warns; do not ignore that warning.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p = &x;

    *p = *p + 5;
    printf("%d\n", x);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`*p` is another name for `x`, so the line reads `x = x + 5`.

</details>

**Q2.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int a = 1, b = 2;
    int *p = &a;
    int *q = &b;

    p = q;
    *p = 9;
    printf("%d %d\n", a, b);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`p = q;` has no star: it copies an address, so `p` now points at `b` as well. `*p = 9;` therefore changes `b`. Nothing ever writes to `a`.

</details>

**Q3.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int v[4] = {10, 20, 30, 40};
    int *p = v;

    p++;
    printf("%d %d\n", *p, *(p + 2));
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`p++` moves the pointer one element forward, to `v[1]`. Two elements further on is `v[3]`.

</details>

**Q4.** Why does `scanf("%d", &n);` need an `&`, while `scanf("%19s", word);` for a `char word[20];` does not?

<details><summary>💡 Show answer</summary>

`scanf` always needs an address. `n` is an `int`, so its address is `&n`. The name of an array already gives the address of its first element, so `word` is what `scanf` needs.

</details>

**Q5.** What is wrong here, and what will probably happen?

```c
int *p;
*p = 5;
```

<details><summary>💡 Show answer</summary>

`p` was never given an address, so it holds whatever bits were in memory. `*p = 5;` writes to that random place. The usual result is a crash. The worse result is no crash and silently damaged data.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (triple)

Write `void triple(int *n)` that multiplies the caller's variable by three. Show that it works.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex1_triple.c
#include <stdio.h>

void triple(int *n)
{
    *n = *n * 3;
}

int main(void)
{
    int value = 7;

    triple(&value);
    printf("%d\n", value);
    return 0;
}
```

</details>

### Exercise 2 (in order)

Write `void swap(double *a, double *b)`. Read two real numbers and use `swap` so that they are printed with the smaller one first.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex2_in_order.c stdin="9.5 2.25"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    double x, y;

    printf("Two numbers: ");
    scanf("%lf %lf", &x, &y);

    if (x > y) {
        swap(&x, &y);
    }
    printf("In order: %.2f %.2f\n", x, y);
    return 0;
}
```

</details>

### Exercise 3 (smallest and largest in one call)

Write `void min_max(const int a[], int n, int *min, int *max)` that stores the smallest and the largest element in the caller's variables. Test it on `{12, 5, 31, 8, 27}`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex3_min_max.c
#include <stdio.h>

void min_max(const int a[], int n, int *min, int *max)
{
    *min = a[0];
    *max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < *min) {
            *min = a[i];
        }
        if (a[i] > *max) {
            *max = a[i];
        }
    }
}

int main(void)
{
    int data[5] = {12, 5, 31, 8, 27};
    int lowest, highest;

    min_max(data, 5, &lowest, &highest);
    printf("min = %d, max = %d\n", lowest, highest);
    return 0;
}
```

</details>

### Exercise 4 (walking pointer)

Write `int sum(const int *start, int n)` that adds `n` elements **without square brackets**: move a pointer along the array with `p++` and read with `*p`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex4_walking_pointer.c
#include <stdio.h>

int sum(const int *start, int n)
{
    int total = 0;

    for (const int *p = start; p < start + n; p++) {   // p visits each element
        total += *p;
    }
    return total;
}

int main(void)
{
    int data[6] = {1, 2, 3, 4, 5, 6};

    printf("%d\n", sum(data, 6));
    return 0;
}
```

*`start + n` is the address just after the last element. It is used as a finishing line and is never dereferenced.*

</details>

### Exercise 5 (four workers)

An array has 10 elements with the values 1 to 10. Use the `sum` function of the `halves.c` example to add it up in **four** parts, as four workers would, and print each part and the grand total. Ten is not divisible by four: give the leftover elements to the last worker.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex5_four_workers.c
#include <stdio.h>

#define N 10
#define WORKERS 4

double sum(const double *data, int n)
{
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

int main(void)
{
    double values[N];
    for (int i = 0; i < N; i++) {
        values[i] = i + 1;
    }

    int chunk = N / WORKERS;         // 2 elements each, 2 left over
    double grand_total = 0.0;

    for (int w = 0; w < WORKERS; w++) {
        int start = w * chunk;
        int count = chunk;
        if (w == WORKERS - 1) {
            count = N - start;       // the last worker takes the rest
        }
        double part = sum(values + start, count);
        printf("Worker %d: elements %d to %d, sum %.0f\n",
               w, start, start + count - 1, part);
        grand_total += part;
    }
    printf("Grand total: %.0f\n", grand_total);
    return 0;
}
```

@@output

</details>

### Exercise 6 (count a letter, a little harder)

Write `int count_char(const char *text, char wanted)` that counts how often a character occurs in a string. Walk through the string with a pointer until you reach the end marker `'\0'`. Count the letter `c` in `"concurrency and communication"`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex6_count_char.c
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
```

</details>

---

## 🔑 Key takeaways

- **`&x`** is the address of `x`; a **pointer** is a variable that stores an address.
- **`*p`** is the variable that `p` points at: reading or writing it reads or writes the original.
- Passing an **address** lets a function change its caller's variables and deliver several results.
- An **array name** is the address of the first element; `p[i]` and `*(p + i)` are the same thing.
- `values + k` with a count lets a function work on **part of an array**.
- A pointer must point at something that **exists**. Check for **`NULL`**, and never return the address of a local variable.
