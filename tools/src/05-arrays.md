## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Declare, initialise and index a one-dimensional array.
- Process every element of an array with a `for` loop: sum, average, maximum.
- Explain why C does not stop you from reading or writing outside an array, and why that is dangerous.
- Combine arrays element by element, as in the vector addition of the first lab.
- Use two-dimensional arrays with nested loops.
- Store and print text as an array of characters.

> **Prerequisites:** Lessons 01 to 04.
>
> 🔭 **Why this lesson matters later:** the data of a parallel program lives in arrays, often with millions of elements. "Thread 0 takes the first half, thread 1 the second half" is a statement about array indices.

## 1. Declaring and using an array

### Intuition first

An array is a row of numbered lockers, all of the same size, next to each other in memory. The row has one name, and each locker is reached by its number. The numbering starts at **zero**.

### Formal definition

`int marks[5];` reserves room for five `int` values. The valid indices are `0` to `4`. The size is part of the declaration and cannot change afterwards.

```c file=examples/marks.c
#include <stdio.h>

#define N 5

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45};

    marks[1] = 61;       // change the second element

    printf("First: %d, last: %d\n", marks[0], marks[N - 1]);

    for (int i = 0; i < N; i++) {
        printf("marks[%d] = %d\n", i, marks[i]);
    }
    return 0;
}
```

@@output

Now the standard loop of Lesson 04 makes sense: `for (int i = 0; i < N; i++)` visits exactly the indices `0` to `N - 1`.

| Declaration | Content |
| --- | --- |
| `int a[5];` | five elements with **undefined** values |
| `int a[5] = {1, 2, 3, 4, 5};` | the listed values |
| `int a[5] = {1, 2};` | `1`, `2`, and zeros for the rest |
| `int a[5] = {0};` | all zeros |
| `int a[] = {7, 8, 9};` | the compiler counts: three elements |

### Why it matters

C does **not** check array indices. `marks[5]` and `marks[-1]` compile and run. They read or overwrite whatever lies next to the array in memory: perhaps another variable, perhaps nothing important, perhaps something that makes the program crash much later. This is the most common serious bug in C programs.

> ⚠️ **Common pitfalls**
>
> - **`i <= N` in the loop.** The last valid index is `N - 1`. With `<=` the loop touches one element beyond the array.
> - **A size that is a variable.** `int n = 5; int a[n];` is not accepted by Visual Studio. Give the size with `#define`. Lesson 08 shows how to choose the size while the program runs.
> - **A huge array inside `main`.** `double data[10000000];` may crash at start-up, because local variables live in a small memory area. Lesson 08 solves this too.
> - **Copying with `=`.** `b = a;` does not copy an array. Copy the elements in a loop.

## 2. Working through an array

Sum, average, smallest and largest all follow the same pattern: a variable before the loop, one look at each element inside it.

```c file=examples/timings.c
#include <stdio.h>

#define RUNS 6

int main(void)
{
    // the same program, timed six times (seconds)
    double times[RUNS] = {2.31, 2.28, 2.45, 2.27, 2.36, 2.30};

    double total = 0.0;
    double best = times[0];          // assume the first is the fastest

    for (int i = 0; i < RUNS; i++) {
        total += times[i];
        if (times[i] < best) {
            best = times[i];
        }
    }

    printf("Average: %.3f s\n", total / RUNS);
    printf("Best:    %.3f s\n", best);
    return 0;
}
```

@@output

## 3. Combining arrays element by element

The first lab of the module adds two arrays: element `i` of the result is the sum of the elements `i` of the two inputs. Here is the ordinary, one-thread version, with small arrays so that you can check the output by eye.

```c file=examples/vector_add.c
#include <stdio.h>

#define N 8

int main(void)
{
    int a[N], b[N], c[N];

    for (int i = 0; i < N; i++) {    // give the inputs some values first
        a[i] = i;
        b[i] = 10 * i;
    }

    for (int i = 0; i < N; i++) {    // the loop that the lab makes parallel
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < N; i++) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }
    return 0;
}
```

@@output

Look at the middle loop. Round 3 reads `a[3]` and `b[3]` and writes `c[3]`. It does not use anything that another round produces. The rounds could run in any order, or at the same time, and the result would be the same. That independence is what makes this loop easy to run in parallel.

## 4. Two-dimensional arrays

`int grid[3][4];` is a table with 3 rows and 4 columns. The first index chooses the row, the second the column. Nested loops walk through it: the outer loop over the rows, the inner loop over the columns.

```c file=examples/matrix.c
#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void)
{
    int grid[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (int r = 0; r < ROWS; r++) {
        int row_total = 0;
        for (int c = 0; c < COLS; c++) {
            printf("%4d", grid[r][c]);
            row_total += grid[r][c];
        }
        printf("   | row total %d\n", row_total);
    }
    return 0;
}
```

@@output

In memory the rows are stored one after another: all of row 0, then all of row 1, and so on.

## 5. Text is an array of characters

C has no separate string type. A **string** is an array of `char` that ends with a special character with code zero, written `'\0'`. That end marker is how functions such as `printf` know where the text stops.

```c file=examples/strings.c
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
```

@@output

To read a word from the keyboard, declare a `char` array that is large enough and write `scanf("%19s", word);` for an array of 20 characters. There is no `&` here, for a reason that Lesson 07 explains, and the number leaves room for the end marker.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int a[5] = {1, 2};

    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

When the list is shorter than the array, the remaining elements are set to zero. Without any list at all, they would hold undefined values.

</details>

**Q2.** For `double x[8];`, which indices are valid? What happens when a program executes `x[8] = 1.0;`?

<details><summary>💡 Show answer</summary>

The valid indices are 0 to 7. `x[8] = 1.0;` compiles and runs, and writes into memory that does not belong to the array. The program may seem to work, may give wrong results, or may crash. C gives no error message.

</details>

**Q3.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int a[4] = {3, 1, 4, 1};

    for (int i = 1; i < 4; i++) {
        a[i] = a[i] + a[i - 1];
    }
    for (int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

Each element becomes the sum of everything up to that position. Round `i` uses `a[i - 1]`, which the round before has just changed.

</details>

**Q4.** In which of these loops are the rounds independent of each other, so that they could run in any order?

```c
for (int i = 0; i < N; i++) c[i] = a[i] + b[i];     // (a)
for (int i = 0; i < N; i++) total += a[i];          // (b)
for (int i = 1; i < N; i++) a[i] = a[i] + a[i - 1]; // (c)
```

<details><summary>💡 Show answer</summary>

Only (a) is fully independent: every round has its own `a[i]`, `b[i]` and `c[i]`. In (b) the order does not change the sum, but all rounds update the same variable `total`, so they cannot simply run at the same time. In (c), as in Q3, each round needs the result of the round before, so the order is fixed.

</details>

**Q5.** What does this program print?

```c check
#include <stdio.h>
#include <string.h>

int main(void)
{
    char word[] = "loop";

    printf("%zu %zu\n", strlen(word), sizeof(word));
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`strlen` counts the letters. `sizeof` gives the size of the array, which has one more element for the end marker `'\0'`.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (above average)

Start from `int marks[8] = {72, 58, 64, 90, 45, 81, 67, 53};`. Print the average with one decimal, and how many marks are above the average.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex1_above_average.c
#include <stdio.h>

#define N 8

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45, 81, 67, 53};
    int total = 0;

    for (int i = 0; i < N; i++) {
        total += marks[i];
    }
    double average = (double) total / N;   // cast, or the decimals are lost

    int above = 0;
    for (int i = 0; i < N; i++) {
        if (marks[i] > average) {
            above++;
        }
    }
    printf("Average: %.1f, above average: %d\n", average, above);
    return 0;
}
```

</details>

### Exercise 2 (smallest and where)

For the same array, print the smallest mark and its index.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex2_smallest.c
#include <stdio.h>

#define N 8

int main(void)
{
    int marks[N] = {72, 58, 64, 90, 45, 81, 67, 53};
    int where = 0;                   // index of the smallest so far

    for (int i = 1; i < N; i++) {
        if (marks[i] < marks[where]) {
            where = i;
        }
    }
    printf("Smallest: %d at index %d\n", marks[where], where);
    return 0;
}
```

*Remembering the index is enough: the value is `marks[where]`.*

</details>

### Exercise 3 (reverse)

Reverse an array **in place**, without a second array, and print it. Test with `{1, 2, 3, 4, 5, 6, 7}`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex3_reverse.c
#include <stdio.h>

#define N 7

int main(void)
{
    int a[N] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < N / 2; i++) {    // stop in the middle
        int temp = a[i];
        a[i] = a[N - 1 - i];
        a[N - 1 - i] = temp;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
```

*Going all the way to `N` would swap every pair twice and restore the original order.*

</details>

### Exercise 4 (dot product)

The dot product of two arrays is `x[0]*y[0] + x[1]*y[1] + ...`. Compute it for `x = {1.0, 2.0, 3.0, 4.0}` and `y = {0.5, 0.25, 2.0, 1.0}`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex4_dot_product.c
#include <stdio.h>

#define N 4

int main(void)
{
    double x[N] = {1.0, 2.0, 3.0, 4.0};
    double y[N] = {0.5, 0.25, 2.0, 1.0};
    double dot = 0.0;

    for (int i = 0; i < N; i++) {
        dot += x[i] * y[i];
    }
    printf("Dot product: %.2f\n", dot);
    return 0;
}
```

</details>

### Exercise 5 (column totals)

For the 3 × 4 `grid` of section 4, print the total of each **column**.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex5_column_totals.c
#include <stdio.h>

#define ROWS 3
#define COLS 4

int main(void)
{
    int grid[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (int c = 0; c < COLS; c++) {         // now the columns are the outer loop
        int total = 0;
        for (int r = 0; r < ROWS; r++) {
            total += grid[r][c];
        }
        printf("Column %d: %d\n", c, total);
    }
    return 0;
}
```

</details>

### Exercise 6 (length of a string)

Read a word of at most 19 letters and print its length **without** using `strlen`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex6_length.c stdin="concurrency"
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
```

</details>

### Exercise 7 (matrix multiplication, a little harder)

Multiply two 3 × 3 matrices `A` and `B` into `C`. Element `C[i][j]` is the dot product of row `i` of `A` and column `j` of `B`: `A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j]`. Use `A = {{1,2,3},{4,5,6},{7,8,9}}` and let `B` be the matrix with 2 on the diagonal and 0 elsewhere, so that the answer is easy to check.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex7_matrix_multiply.c
#include <stdio.h>

#define N 3

int main(void)
{
    int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[N][N] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    int C[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;                         // an accumulator per element
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

@@output

*Three nested loops: for matrices of size N the innermost line runs N × N × N times. Matrix multiplication is a standard test program for parallel computers for that reason.*

</details>

---

## 🔑 Key takeaways

- An array is a fixed number of elements of one type; indices run from **`0` to `N - 1`**.
- C does **not check indices**. Going outside an array is a silent and serious bug.
- **`for (int i = 0; i < N; i++)`** is the loop that visits every element.
- A loop whose rounds each touch **their own elements** has independent rounds.
- A 2D array is indexed **`[row][column]`** and processed with nested loops.
- A **string** is a `char` array that ends with `'\0'`.
