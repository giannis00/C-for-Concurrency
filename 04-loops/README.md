# 📘 Lesson 04: Loops
### Course: *C for Concurrency*
**Instructor:** Ioannis Tsioulis  
*Part 1: C refresher · Lesson 4 of 9*

[⬅ Course home](../README.md) · [How to run the code](../SETUP.md) · [Online C compiler](https://www.onlinegdb.com/online_c_compiler)

---

## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Repeat statements with `while`, `for` and `do`-`while`, and choose the right one.
- Name the three parts of a `for` loop and say when each one runs.
- Count exactly how many times a loop body is executed.
- Leave a loop early with `break` and skip one round with `continue`.
- Write nested loops, and build up a result with an accumulator variable.

> **Prerequisites:** Lessons 01 to 03.
>
> 🔭 **Why this lesson matters later:** almost all the time of a numerical program is spent inside `for` loops. Parallel programming, to a large extent, is the art of sharing the iterations of a loop between several threads.

## 1. The `while` loop

### Intuition first

"While there is still coffee in the cup, take a sip." The condition is checked **before** every round. If it is false at the start, the body never runs.

📄 [`examples/countdown.c`](examples/countdown.c)

```c
#include <stdio.h>

int main(void)
{
    int n = 5;

    while (n > 0) {
        printf("%d ", n);
        n--;                 // without this line the loop never ends
    }
    printf("Lift-off!\n");
    return 0;
}
```

**Output**

```text
5 4 3 2 1 Lift-off!
```

### Why it matters

`while` is the natural choice when you **do not know in advance** how many rounds are needed.

📄 [`examples/halving.c`](examples/halving.c)

```c
#include <stdio.h>

int main(void)
{
    int value = 1000;
    int steps = 0;

    while (value > 1) {
        value = value / 2;   // integer division
        steps++;
    }
    printf("1000 can be halved %d times.\n", steps);
    return 0;
}
```

**Output**

```text
1000 can be halved 9 times.
```

## 2. The `for` loop

### Formal definition

A `for` loop puts the three things that every counting loop needs on one line:

```c
for (initialisation; condition; update) {
    body
}
```

| Part | Runs | Typical content |
| --- | --- | --- |
| initialisation | once, before anything else | `int i = 0` |
| condition | before every round; the loop ends when it is false | `i < N` |
| update | after every round | `i++` |

📄 [`examples/sum.c`](examples/sum.c)

```c
#include <stdio.h>

#define N 100

int main(void)
{
    int total = 0;               // the accumulator starts empty

    for (int i = 1; i <= N; i++) {
        total += i;              // add one more number in every round
    }
    printf("1 + 2 + ... + %d = %d\n", N, total);
    return 0;
}
```

**Output**

```text
1 + 2 + ... + 100 = 5050
```

`total` is an **accumulator**: a variable declared before the loop that collects a result round by round. A variable declared inside the brackets of the `for`, like `i`, exists only inside that loop.

### The standard counting loop

C programmers count from zero: `for (int i = 0; i < N; i++)` runs exactly `N` times, with `i` going from `0` to `N - 1`. Lesson 05 shows why: these are the positions of an array with `N` elements.

> ⚠️ **Common pitfalls**
>
> - **One round too many or too few.** `i < N` and `i <= N` differ by one round. Check the first and the last value of `i` by hand.
> - **An endless loop.** If nothing in the body changes the condition, the loop never stops. In a terminal, `Ctrl+C` stops the program.
> - **A semicolon after the brackets.** `for (...);` is a loop with an empty body. The block below it runs once.
> - **Testing a `double` for equality.** `for (double x = 0; x != 1.0; x += 0.1)` never ends, because adding 0.1 ten times does not give exactly 1.0. Count with an `int`.

## 3. The `do`-`while` loop

`do`-`while` checks its condition **after** the body, so the body runs at least once. That fits "ask, then check the answer".

📄 [`examples/validate.c`](examples/validate.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int mark;

    do {
        printf("Mark (0-100): ");
        scanf("%d", &mark);
    } while (mark < 0 || mark > 100);   // note the semicolon

    printf("Accepted: %d\n", mark);
    return 0;
}
```

**Example run**

```text
Mark (0-100): 150
Mark (0-100): -3
Mark (0-100): 64
Accepted: 64
```

## 4. `break` and `continue`

| Statement | Effect |
| --- | --- |
| `break;` | leaves the loop at once |
| `continue;` | skips the rest of this round and goes on with the next one |

📄 [`examples/break_continue.c`](examples/break_continue.c)

```c
#include <stdio.h>

int main(void)
{
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            continue;        // skip the multiples of 3
        }
        if (i > 7) {
            break;           // stop the whole loop
        }
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
```

**Output**

```text
1 2 4 5 7 
```

## 5. Nested loops

A loop inside a loop: for **each** round of the outer loop, the inner loop runs completely. Think of the hands of a clock: the minute hand goes all the way round for every step of the hour hand.

📄 [`examples/table.c`](examples/table.c)

```c
#include <stdio.h>

int main(void)
{
    for (int row = 1; row <= 4; row++) {
        for (int col = 1; col <= 6; col++) {
            printf("%4d", row * col);
        }
        printf("\n");        // end of the row
    }
    return 0;
}
```

**Output**

```text
   1   2   3   4   5   6
   2   4   6   8  10  12
   3   6   9  12  15  18
   4   8  12  16  20  24
```

The body of the inner loop ran 4 × 6 = 24 times. Nested loops multiply, which is why they dominate the running time of a program.

> 🧠 **A first look at parallel loops.** A `for` loop with a known number of rounds is the kind of loop that can be shared between threads. It is easy when the rounds are independent of each other. It needs care when every round updates the same variable, as `total += i` does: two threads that change `total` at the same moment can lose an update. That problem is called a *race condition*, and you will meet it again.

---

## 🧠 Check your understanding

**Q1.** How many times does the body of each loop run?

```c
for (int i = 0; i < 10; i++)  { ... }    // (a)
for (int i = 1; i <= 10; i++) { ... }    // (b)
for (int i = 0; i <= 10; i++) { ... }    // (c)
for (int i = 10; i > 0; i -= 2) { ... }  // (d)
```

<details><summary>💡 Show answer</summary>

(a) 10 times, `i` from 0 to 9. (b) 10 times, `i` from 1 to 10. (c) 11 times, `i` from 0 to 10. (d) 5 times, `i` = 10, 8, 6, 4, 2.

</details>

**Q2.** What does this program print?

```c
#include <stdio.h>

int main(void)
{
    int i = 0;

    while (i < 5) {
        i += 2;
    }
    printf("%d\n", i);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
6
```

`i` takes the values 2, 4 and 6. The loop stops at the first value for which `i < 5` is false, and that value is 6, not 5.

</details>

**Q3.** What does this program print?

```c
#include <stdio.h>

int main(void)
{
    int count = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
12
```

The inner body runs 3 times for each of the 4 outer rounds.

</details>

**Q4.** What does this program print?

```c
#include <stdio.h>

int main(void)
{
    int n = 10;

    do {
        printf("%d ", n);
        n++;
    } while (n < 5);
    printf("\n");
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
10 
```

The condition is false from the start, but a `do`-`while` runs its body once before it checks. A `while` loop with the same condition would print nothing.

</details>

**Q5.** What does this fragment print?

```c
int i;
for (i = 0; i < 3; i++);
{
    printf("%d\n", i);
}
```

<details><summary>💡 Show answer</summary>

`3`, once. The semicolon after the brackets is the whole body of the loop, so the loop only counts to 3. The block below is an ordinary block that runs one time.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (sum to n)

Read a positive integer `n` and print the sum 1 + 2 + ... + n.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex1_sum_to_n.c`](solutions/ex1_sum_to_n.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n, total = 0;

    printf("n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        total += i;
    }
    printf("Sum: %d\n", total);
    return 0;
}
```

</details>

### Exercise 2 (multiplication table)

Read an integer and print its multiplication table from 1 to 10, one line per product, like `7 x 3 = 21`.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex2_times_table.c`](solutions/ex2_times_table.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;

    printf("Table of: ");
    scanf("%d", &n);

    for (int i = 1; i <= 10; i++) {
        printf("%d x %2d = %3d\n", n, i, n * i);
    }
    return 0;
}
```

</details>

### Exercise 3 (factorial)

Read `n` (at most 20) and print n! = 1 × 2 × ... × n. Factorials grow quickly and no longer fit in an `int` from 13! onwards. Use the type `long long`, which is printed with `%lld`.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex3_factorial.c`](solutions/ex3_factorial.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;
    long long factorial = 1;     // a product starts at 1, not at 0

    printf("n (0-20): ");
    scanf("%d", &n);

    for (int i = 2; i <= n; i++) {
        factorial *= i;
    }
    printf("%d! = %lld\n", n, factorial);
    return 0;
}
```

</details>

### Exercise 4 (count the digits)

Read a positive integer and print how many digits it has. You do not know the number of rounds in advance, so use `while`.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex4_digits.c`](solutions/ex4_digits.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n, digits = 0;

    printf("A positive integer: ");
    scanf("%d", &n);

    while (n > 0) {
        n /= 10;        // integer division removes the last digit
        digits++;
    }
    printf("Digits: %d\n", digits);
    return 0;
}
```

</details>

### Exercise 5 (triangle)

Read a number of rows and print a triangle of stars. For 4 rows:

```text
*
**
***
****
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex5_triangle.c`](solutions/ex5_triangle.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int rows;

    printf("Rows: ");
    scanf("%d", &rows);

    for (int row = 1; row <= rows; row++) {
        for (int star = 0; star < row; star++) {   // row number = number of stars
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
```

</details>

### Exercise 6 (prime or not)

Read an integer greater than 1 and print whether it is prime. Try the divisors 2, 3, 4, ... and stop at the first one that divides the number.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex6_prime.c`](solutions/ex6_prime.c)

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;
    int is_prime = 1;            // assume prime until a divisor is found

    printf("An integer above 1: ");
    scanf("%d", &n);

    for (int d = 2; d * d <= n; d++) {   // no need to go beyond the square root
        if (n % d == 0) {
            is_prime = 0;
            break;
        }
    }

    if (is_prime) {
        printf("%d is prime.\n", n);
    } else {
        printf("%d is not prime.\n", n);
    }
    return 0;
}
```

</details>

### Exercise 7 (computing π, a little harder)

The area under the curve 4 / (1 + x²) between 0 and 1 is exactly π. Approximate it by cutting the interval into `N` strips of width `1.0 / N` and adding the areas of `N` rectangles. The height of rectangle `i` is the value of the curve in the middle of the strip, at x = (i + 0.5) × width. Use `N` = 1,000,000 and print the result with 10 decimals.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex7_pi.c`](solutions/ex7_pi.c)

```c
#include <stdio.h>

#define N 1000000

int main(void)
{
    const double width = 1.0 / N;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * width;    // middle of strip i
        sum += 4.0 / (1.0 + x * x);      // height of the curve there
    }
    printf("pi is about %.10f\n", sum * width);
    return 0;
}
```

**Output**

```text
pi is about 3.1415926536
```

*This loop is a classic first exercise in parallel programming: a million independent heights, added into one accumulator.*

</details>

---

## 🔑 Key takeaways

- **`while`** checks first and suits an unknown number of rounds; **`do`-`while`** runs at least once.
- **`for (int i = 0; i < N; i++)`** runs exactly `N` times, with `i` from `0` to `N - 1`.
- An **accumulator** is declared before the loop and updated inside it.
- **`break`** leaves the loop; **`continue`** jumps to the next round.
- **Nested loops** multiply their numbers of rounds.
- Count loops with an **`int`**, never by testing a `double` for equality.


---

**Next:** [Lesson 05: Arrays](../05-arrays/README.md), where loops get data to work on.

*© Ioannis Tsioulis. *C for Concurrency*. Prepared for educational use.*
