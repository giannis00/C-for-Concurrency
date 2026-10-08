## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Explain the difference between the stack and the heap, and why large arrays belong on the heap.
- Allocate an array with `malloc`, check that the allocation worked, and release it with `free`.
- Use `calloc` for zero-filled memory and `realloc` to change the size of a block.
- Write a function that creates an array and returns it to its caller.
- Recognise memory leaks, use after `free`, and writing beyond an allocated block.

> **Prerequisites:** Lessons 01 to 07. Pointers (Lesson 07) are essential here.
>
> 🔭 **Why this lesson matters later:** to see a parallel program beat a serial one, you need problems that take a while: arrays with millions of elements. Arrays of that size cannot be ordinary local variables.

## 1. Why ordinary arrays are not enough

### Intuition first

The local variables of your functions live in a region of memory called the **stack**. It works like a pile of trays: each function call puts its variables on top, and takes them away again when it returns. The stack is fast and automatic, but small.

The **heap** is a large store-room. You ask for a block of any size while the program is running, you keep it for as long as you like, and you give it back yourself.

| | Stack (local variables) | Heap (`malloc`) |
| --- | --- | --- |
| Size of an array | fixed when you write the program | decided while the program runs |
| Space available | small: typically 1 MB with Visual Studio, 8 MB on Linux | as much as the machine can give |
| Lifetime | until the function returns | until you call `free` |
| Who cleans up | automatic | you |

An array of one million `double` values takes 8 MB. As a local variable it already fills or overflows the stack, and the program crashes as soon as it starts.

## 2. `malloc` and `free`

### Formal definition

Both functions are announced in `stdlib.h`.

| Call | Meaning |
| --- | --- |
| `malloc(bytes)` | asks for a block of that many bytes and returns its address, or `NULL` if no memory is available |
| `free(pointer)` | gives the block back |

The size of an array in bytes is the number of elements times the size of one element, so the standard line is `type *name = malloc(n * sizeof(type));`. After that, the pointer is used with square brackets exactly like an array (Lesson 07, section 4).

```c file=examples/dynamic_array.c stdin="6"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>              // malloc and free

int main(void)
{
    int n;

    printf("How many squares? ");
    scanf("%d", &n);

    int *squares = malloc(n * sizeof(int));    // room for n ints
    if (squares == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        squares[i] = i * i;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");

    free(squares);               // give the block back
    return 0;
}
```

@@output

The four steps are always the same: **allocate, check, use, free**.

> 🛠️ If Visual Studio reports that it "cannot convert from `void *`", your file is being compiled as C++, usually because its name ends in `.cpp`. Rename it to `.c`.

### A large array

```c file=examples/big_array.c
#include <stdio.h>
#include <stdlib.h>

#define N 5000000                // five million elements

int main(void)
{
    double *data = malloc(N * sizeof(double));
    if (data == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }
    printf("Allocated %.0f MB\n", N * sizeof(double) / (1024.0 * 1024.0));

    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    double total = 0.0;
    for (int i = 0; i < N; i++) {
        total += data[i];
    }
    printf("Sum: %.0f\n", total);

    free(data);
    return 0;
}
```

@@output

Declared as `double data[N];` inside `main`, the same array would not fit on the stack.

## 3. `calloc` and `realloc`

| Call | Meaning |
| --- | --- |
| `calloc(n, sizeof(type))` | like `malloc`, but every byte of the block is set to zero |
| `realloc(pointer, new_bytes)` | changes the size of a block and keeps its contents; the block may **move**, so use the address that `realloc` returns |

Memory from `malloc` holds undefined values, like any other uninitialised variable. Use `calloc` when you want counters or sums that start at zero.

`realloc` makes it possible to store data whose amount you do not know in advance. A common plan is to double the capacity whenever the block is full.

```c file=examples/grow.c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int capacity = 2;            // how many elements fit
    int count = 0;               // how many are in use
    int *list = malloc(capacity * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    for (int value = 10; value <= 70; value += 10) {
        if (count == capacity) {             // full: ask for twice as much
            capacity *= 2;
            int *bigger = realloc(list, capacity * sizeof(int));
            if (bigger == NULL) {
                free(list);
                return 1;
            }
            list = bigger;
            printf("(capacity is now %d)\n", capacity);
        }
        list[count] = value;
        count++;
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}
```

@@output

## 4. Functions that create arrays

Lesson 07 warned against returning the address of a local variable, because the variable disappears when the function returns. A block from `malloc` does **not** disappear. A function can allocate it, fill it and return its address.

```c file=examples/ramp.c
#include <stdio.h>
#include <stdlib.h>

// returns a new array: start, start + step, start + 2 * step, ...
// the caller must free it
double *make_ramp(int n, double start, double step)
{
    double *ramp = malloc(n * sizeof(double));
    if (ramp == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        ramp[i] = start + i * step;
    }
    return ramp;
}

int main(void)
{
    double *x = make_ramp(5, 0.0, 0.25);
    if (x == NULL) {
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%.2f ", x[i]);
    }
    printf("\n");

    free(x);                     // allocated in make_ramp, freed here
    return 0;
}
```

@@output

Say in a comment who is responsible for the `free`. The compiler does not keep track of it for you.

## 5. What can go wrong

| Mistake | What happens |
| --- | --- |
| **Memory leak**: a block is never freed, or its only pointer is overwritten | the program uses more and more memory |
| **Use after free**: reading or writing a block after `free` | wrong values or a crash, often much later |
| **Double free**: calling `free` twice for the same block | usually a crash |
| **Writing beyond the block**: `data[n]` in a block of `n` elements | other data is silently damaged |
| **Forgetting `sizeof`**: `malloc(n)` instead of `malloc(n * sizeof(double))` | the block is eight times too small |

> ⚠️ **Common pitfalls**
>
> - **Not checking for `NULL`.** A request for a very large block can fail. Using the `NULL` that comes back crashes the program.
> - **Losing the address.** `data = malloc(...)` a second time, without `free` in between, leaks the first block: nothing points at it any more.
> - **Freeing something that did not come from `malloc`.** Ordinary arrays and local variables are never passed to `free`.

> 🧠 Every `malloc` is matched by exactly one `free`. When you read a program, find the pairs.

---

## 🧠 Check your understanding

**Q1.** A `double` takes 8 bytes. How many bytes does `malloc(100 * sizeof(double))` ask for? How many `double` values fit in the block returned by `malloc(100)`?

<details><summary>💡 Show answer</summary>

800 bytes, room for 100 values. `malloc(100)` asks for 100 bytes, room for only 12 values. A loop that then fills 100 elements writes far beyond the block.

</details>

**Q2.** What does this program print?

```c check
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *a = calloc(4, sizeof(int));
    if (a == NULL) {
        return 1;
    }

    a[1] = 5;
    printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);

    free(a);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`calloc` sets the whole block to zero. With `malloc` the three elements that were never assigned would hold undefined values.

</details>

**Q3.** What is wrong with this fragment?

```c
int *a = malloc(10 * sizeof(int));
a = malloc(20 * sizeof(int));
free(a);
```

<details><summary>💡 Show answer</summary>

The second assignment overwrites the only pointer to the first block. That block can never be freed: a memory leak. Either `free(a)` before the second `malloc`, or use `realloc`.

</details>

**Q4.** What is wrong with this fragment?

```c
free(data);
printf("%f\n", data[0]);
```

<details><summary>💡 Show answer</summary>

It uses the block after giving it back. The memory may already have been handed to someone else. Call `free` only when you have finished with the data.

</details>

**Q5.** A program declares `double grid[2000][2000];` inside `main`. How much memory is that, and what is likely to happen?

<details><summary>💡 Show answer</summary>

2000 × 2000 × 8 bytes = 32,000,000 bytes, about 30 MB. That is far more than the stack offers, so the program crashes when it starts. Allocate the grid with `malloc`, as in Exercise 4.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (as many marks as you like)

Ask how many marks there are, allocate an array of that size, read the marks and print their average with one decimal.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex1_marks.c stdin="4\n70 55 82 64"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;

    printf("How many marks? ");
    scanf("%d", &n);

    double *marks = malloc(n * sizeof(double));
    if (marks == NULL) {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter the marks: ");
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &marks[i]);     // the address of element i
        total += marks[i];
    }
    printf("Average: %.1f\n", total / n);

    free(marks);
    return 0;
}
```

</details>

### Exercise 2 (a real copy)

Write `int *copy_array(const int *source, int n)` that returns a new array with the same contents. In `main`, copy an array, change the first element of the copy, and show that the original is unchanged.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex2_copy.c
#include <stdio.h>
#include <stdlib.h>

// returns a new array that the caller must free
int *copy_array(const int *source, int n)
{
    int *copy = malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = source[i];
    }
    return copy;
}

int main(void)
{
    int original[4] = {1, 2, 3, 4};

    int *copy = copy_array(original, 4);
    if (copy == NULL) {
        return 1;
    }

    copy[0] = 99;
    printf("original[0] = %d, copy[0] = %d\n", original[0], copy[0]);

    free(copy);
    return 0;
}
```

*Compare with `int *alias = original;`, which copies only the address: then both names would refer to the same four elements.*

</details>

### Exercise 3 (read until zero)

Read positive integers until the user types 0. You do not know how many will come, so start with room for 2 and double the capacity with `realloc` whenever the block is full. At the end print the numbers in reverse order.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex3_until_zero.c stdin="5\n12\n7\n30\n2\n0"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int capacity = 2, count = 0;
    int *numbers = malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    int value;
    printf("Number (0 to stop): ");
    scanf("%d", &value);

    while (value != 0) {
        if (count == capacity) {
            capacity *= 2;
            int *bigger = realloc(numbers, capacity * sizeof(int));
            if (bigger == NULL) {
                free(numbers);
                return 1;
            }
            numbers = bigger;
        }
        numbers[count] = value;
        count++;

        printf("Number (0 to stop): ");
        scanf("%d", &value);
    }

    printf("In reverse:");
    for (int i = count - 1; i >= 0; i--) {
        printf(" %d", numbers[i]);
    }
    printf("\n");

    free(numbers);
    return 0;
}
```

</details>

### Exercise 4 (a matrix in one block)

Large matrices are usually stored as **one** block of `rows * cols` elements, row after row. The element in row `r` and column `c` is then at index `r * cols + c`. Allocate a 3 × 5 matrix of `int` in this way, set each element to `10 * r + c`, and print it as a table.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex4_flat_matrix.c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rows = 3, cols = 5;

    int *m = malloc(rows * cols * sizeof(int));
    if (m == NULL) {
        return 1;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            m[r * cols + c] = 10 * r + c;    // skip r full rows, then c elements
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%4d", m[r * cols + c]);
        }
        printf("\n");
    }

    free(m);
    return 0;
}
```

@@output

*One block means one `malloc`, one `free`, and all the elements next to each other in memory. It is also the form in which a matrix can be handed to another process in one piece.*

</details>

### Exercise 5 (a big dot product, a little harder)

Write `double *create_filled(int n, double value)` that returns a new array of `n` elements, all equal to `value`. Use it to create two arrays of 1,000,000 elements, one filled with 1.5 and one with 2.0, compute their dot product (Lesson 05, Exercise 4) and free both arrays. What result do you expect before you run it?

<details><summary>💡 Show solution</summary>

```c file=solutions/ex5_big_dot_product.c
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

// returns a new array that the caller must free
double *create_filled(int n, double value)
{
    double *a = malloc(n * sizeof(double));
    if (a == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        a[i] = value;
    }
    return a;
}

int main(void)
{
    double *x = create_filled(N, 1.5);
    double *y = create_filled(N, 2.0);
    if (x == NULL || y == NULL) {
        free(x);                 // free(NULL) is allowed and does nothing
        free(y);
        return 1;
    }

    double dot = 0.0;
    for (int i = 0; i < N; i++) {
        dot += x[i] * y[i];
    }
    printf("Dot product: %.1f\n", dot);

    free(x);
    free(y);
    return 0;
}
```

@@output

*Each product is 3.0 and there are a million of them. Knowing the answer in advance is the simplest test that a program is correct, and you will rely on such tests when you make programs parallel.*

</details>

---

## 🔑 Key takeaways

- Local variables live on the small **stack**; `malloc` takes memory from the large **heap**.
- **`malloc(n * sizeof(type))`** returns the address of a block, or **`NULL`** on failure.
- The pattern is always **allocate, check, use, free**.
- **`calloc`** gives zero-filled memory; **`realloc`** changes the size of a block and may move it.
- Heap memory **outlives the function** that allocated it, so a function can return a new array.
- Every `malloc` needs exactly one **`free`**: no leak, no use after free, no double free.
