# 📘 Lesson 06: Functions
### Course: *C for Concurrency*
**Instructor:** Ioannis Tsioulis  
*Part 1: C refresher · Lesson 6 of 9*

[⬅ Course home](../README.md) · [How to run the code](../SETUP.md) · [Online C compiler](https://www.onlinegdb.com/online_c_compiler)

---

## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Define a function with parameters and a return value, and call it.
- Write a prototype, and explain why the compiler needs one.
- Use functions from a library header such as `math.h`.
- Explain what "pass by value" means, and predict when a function can change its caller's data.
- Pass an array to a function together with its size.
- Tell local variables from global variables.

> **Prerequisites:** Lessons 01 to 05.
>
> 🔭 **Why this lesson matters later:** the work of a thread is written as a function, and the OpenMP and MPI libraries are collections of functions that you call. Global variables, introduced at the end of this lesson, are the data that threads share.

## 1. Defining and calling a function

### Intuition first

A function is a named recipe. You write it once and use it as often as you like. The caller hands over ingredients (the **arguments**) and may get something back (the **return value**).

### Formal definition

```c
return_type name(type parameter1, type parameter2)
{
    statements
    return value;
}
```

A function that returns nothing has the return type `void`. A function without parameters has `void` between the brackets.

📄 [`examples/functions.c`](examples/functions.c)

```c
#include <stdio.h>

double average(double a, double b)       // two parameters, returns a double
{
    return (a + b) / 2;
}

void print_line(int length)              // returns nothing
{
    for (int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}

int main(void)
{
    print_line(20);
    printf("Average: %.2f\n", average(3, 4.5));
    print_line(20);
    return 0;
}
```

**Output**

```text
--------------------
Average: 3.75
--------------------
```

`return` ends the function at once and hands the value to the caller. `main` is a function like any other, called by the operating system.

## 2. Prototypes and headers

### Intuition first

The compiler reads a file from top to bottom, once. When it meets a call, it must already know the name of the function, the types of its parameters and its return type. Either the whole function is defined above the call, or a one-line announcement, the **prototype**, stands above it.

📄 [`examples/prototype.c`](examples/prototype.c)

```c
#include <stdio.h>
#include <math.h>                         // announces sqrt, pow, fabs, ...

double hypotenuse(double a, double b);    // prototype: ends with a semicolon

int main(void)
{
    printf("Hypotenuse: %.2f\n", hypotenuse(3.0, 4.0));
    return 0;
}

double hypotenuse(double a, double b)     // the definition can now come later
{
    return sqrt(a * a + b * b);
}
```

**Output**

```text
Hypotenuse: 5.00
```

### Why it matters

A **header file** is mostly a list of prototypes. `#include <stdio.h>` pastes in the prototype of `printf`; `#include <math.h>` pastes in those of the mathematical functions. The parallel programming libraries work in the same way: you will include `omp.h` to be able to call the OpenMP functions.

| Form | Where the file is searched |
| --- | --- |
| `#include <name.h>` | among the headers that come with the compiler and its libraries |
| `#include "name.h"` | first in the folder of your own project |

> 🛠️ With `gcc` on Linux, a program that uses `math.h` is built with `-lm` at the end of the command: `gcc prototype.c -o prototype -lm`. Visual Studio and the online compilers need nothing extra.

## 3. Arguments are passed by value

### Intuition first

When you call a function, each parameter receives a **copy** of the argument. It is like handing someone a photocopy: whatever they write on it, your original does not change.

📄 [`examples/by_value.c`](examples/by_value.c)

```c
#include <stdio.h>

void add_ten(int x)
{
    x = x + 10;                  // changes the copy only
    printf("inside the function: %d\n", x);
}

int main(void)
{
    int n = 5;

    add_ten(n);
    printf("back in main:        %d\n", n);
    return 0;
}
```

**Output**

```text
inside the function: 15
back in main:        5
```

A function can therefore give exactly one thing back: its return value. A function `swap(a, b)` that should exchange two variables of its caller cannot work this way. Lesson 07 shows the way round this.

## 4. Arrays as arguments

Arrays are the exception: an array is **not** copied. The function receives the location of the original array, so it can change the caller's elements. It does not receive the length, so the size is passed as a second argument.

📄 [`examples/array_args.c`](examples/array_args.c)

```c
#include <stdio.h>

#define N 5

double sum(const double data[], int n)   // const: this function only reads
{
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += data[i];
    }
    return total;
}

void scale(double data[], int n, double factor)   // this one changes the array
{
    for (int i = 0; i < n; i++) {
        data[i] *= factor;
    }
}

int main(void)
{
    double values[N] = {1.0, 2.0, 3.0, 4.0, 5.0};

    printf("Sum before: %.1f\n", sum(values, N));
    scale(values, N, 10.0);
    printf("Sum after:  %.1f\n", sum(values, N));
    return 0;
}
```

**Output**

```text
Sum before: 15.0
Sum after:  150.0
```

The word `const` is a promise that the function will not modify the elements. The compiler enforces it, and the reader learns something from the first line alone.

> ⚠️ **Common pitfalls**
>
> - **Forgetting the `return`.** A function declared `int` or `double` that reaches its end without `return` gives back a meaningless value.
> - **Using `sizeof` on an array parameter.** Inside the function, `sizeof(data)` is not the size of the caller's array. Always pass the length.
> - **Mismatched prototype and definition.** If they differ in a type, the compiler reports conflicting types. Copy the first line and add a semicolon.
> - **Calling with brackets missing.** `print_line;` compiles and does nothing. A call always has brackets: `print_line(20);`.

## 5. Local and global variables

| | Local variable | Global variable |
| --- | --- | --- |
| Declared | inside a function | outside every function |
| Visible | only in that function | in every function below it |
| Lives | from the call until the function returns | for the whole run of the program |
| Initial value | undefined | zero |

📄 [`examples/scope.c`](examples/scope.c)

```c
#include <stdio.h>

int calls = 0;                   // global: one variable for the whole program

void work(void)
{
    int steps = 0;               // local: created again at every call

    steps++;
    calls++;
    printf("steps = %d, calls = %d\n", steps, calls);
}

int main(void)
{
    work();
    work();
    work();
    return 0;
}
```

**Output**

```text
steps = 1, calls = 1
steps = 1, calls = 2
steps = 1, calls = 3
```

Globals look convenient, but any function can change them, which makes mistakes hard to trace. Prefer parameters and return values.

> 🧠 In a program with several threads, each thread gets its own copies of the local variables of the function it runs, while global variables exist once and are **shared** by all threads. Most bugs in parallel programs come from shared data.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c
#include <stdio.h>

void twice(int x)
{
    x = x * 2;
}

int main(void)
{
    int a = 7;

    twice(a);
    printf("%d\n", a);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
7
```

`twice` doubles its own copy of the value. Nothing is returned and `a` is untouched. A working version is `int twice(int x) { return x * 2; }`, called as `a = twice(a);`.

</details>

**Q2.** And this one?

```c
#include <stdio.h>

void clear(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

int main(void)
{
    int v[3] = {1, 2, 3};

    clear(v, 3);
    printf("%d %d %d\n", v[0], v[1], v[2]);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
0 0 0
```

An array argument is not copied. The function works on the caller's elements.

</details>

**Q3.** What does this program print?

```c
#include <stdio.h>

double half(int n)
{
    return n / 2;
}

int main(void)
{
    printf("%.1f\n", half(5));
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
2.0
```

`n / 2` is an integer division, which gives 2. Only then is the result converted to the return type `double`. Write `return n / 2.0;`.

</details>

**Q4.** What does this program print?

```c
#include <stdio.h>

int counter(void)
{
    int count = 0;

    count++;
    return count;
}

int main(void)
{
    counter();
    counter();
    printf("%d\n", counter());
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
1
```

`count` is local. It is created, set to 0, raised to 1 and thrown away at every call. To count the calls it would have to be a global variable.

</details>

**Q5.** A file contains `main` first and, below it, the definition of `double area(double r)`. `main` calls `area(2.0)`. There is no prototype. What happens?

<details><summary>💡 Show answer</summary>

When the compiler reaches the call it has not yet seen `area`, so it does not know the types involved. Depending on the compiler this is an error or a warning followed by a wrong guess. Add the prototype `double area(double r);` above `main`, or move the definition up.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (is it even?)

Write `int is_even(int n)` that returns 1 when `n` is even and 0 otherwise. Test it on 4 and 7.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex1_is_even.c`](solutions/ex1_is_even.c)

```c
#include <stdio.h>

int is_even(int n)
{
    return n % 2 == 0;       // a comparison already gives 1 or 0
}

int main(void)
{
    printf("%d %d\n", is_even(4), is_even(7));
    return 0;
}
```

</details>

### Exercise 2 (power)

Write `double power(double base, int exponent)` for exponents of zero or more, with a loop and without `math.h`. Print 2 to the power 10 and 1.5 to the power 3.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex2_power.c`](solutions/ex2_power.c)

```c
#include <stdio.h>

double power(double base, int exponent)
{
    double result = 1.0;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main(void)
{
    printf("%.1f\n", power(2.0, 10));
    printf("%.3f\n", power(1.5, 3));
    return 0;
}
```

</details>

### Exercise 3 (primes below 50)

Turn the prime test of Lesson 04 into a function `int is_prime(int n)` and use it to print all the primes below 50. Put a prototype above `main` and the definition below it.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex3_primes.c`](solutions/ex3_primes.c)

```c
#include <stdio.h>

int is_prime(int n);

int main(void)
{
    for (int n = 2; n < 50; n++) {
        if (is_prime(n)) {
            printf("%d ", n);
        }
    }
    printf("\n");
    return 0;
}

int is_prime(int n)
{
    if (n < 2) {
        return 0;
    }
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return 0;        // a divisor: leave the function at once
        }
    }
    return 1;
}
```

*With `return` inside the loop there is no need for a flag variable and a `break`.*

</details>

### Exercise 4 (largest element)

Write `double largest(const double data[], int n)` that returns the largest element. Test it on `{2.5, 9.1, 4.0, 7.7}`.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex4_largest.c`](solutions/ex4_largest.c)

```c
#include <stdio.h>

double largest(const double data[], int n)
{
    double best = data[0];

    for (int i = 1; i < n; i++) {
        if (data[i] > best) {
            best = data[i];
        }
    }
    return best;
}

int main(void)
{
    double values[4] = {2.5, 9.1, 4.0, 7.7};

    printf("Largest: %.1f\n", largest(values, 4));
    return 0;
}
```

</details>

### Exercise 5 (fill and print)

Write `void fill(int a[], int n, int value)` that sets every element to `value`, and `void print_array(const int a[], int n)` that prints the elements on one line. Use them on an array of 6 elements.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex5_fill_print.c`](solutions/ex5_fill_print.c)

```c
#include <stdio.h>

void fill(int a[], int n, int value)
{
    for (int i = 0; i < n; i++) {
        a[i] = value;
    }
}

void print_array(const int a[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int a[6];

    fill(a, 6, 7);
    print_array(a, 6);
    return 0;
}
```

</details>

### Exercise 6 (how good is the approximation? a little harder)

Turn the π program of Lesson 04 into a function `double approximate_pi(int steps)`. Call it with 10, 100, 1000 and 10000 steps, and print for each the result and its distance from the true value. Use `fabs` from `math.h` for the absolute value, and the format `%.2e`, which prints very small numbers in scientific notation.

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex6_pi_accuracy.c`](solutions/ex6_pi_accuracy.c)

```c
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double approximate_pi(int steps)
{
    const double width = 1.0 / steps;
    double sum = 0.0;

    for (int i = 0; i < steps; i++) {
        double x = (i + 0.5) * width;
        sum += 4.0 / (1.0 + x * x);
    }
    return sum * width;
}

int main(void)
{
    printf("%8s %14s %10s\n", "steps", "result", "error");
    for (int steps = 10; steps <= 10000; steps *= 10) {
        double result = approximate_pi(steps);
        printf("%8d %14.10f %10.2e\n", steps, result, fabs(result - PI));
    }
    return 0;
}
```

**Output**

```text
   steps         result      error
      10   3.1424259850   8.33e-04
     100   3.1416009869   8.33e-06
    1000   3.1415927369   8.33e-08
   10000   3.1415926544   8.33e-10
```

*Ten times more steps make the error a hundred times smaller. More accuracy costs more loop rounds, and that cost is the reason to run the loop in parallel.*

</details>

---

## 🔑 Key takeaways

- A function has a **return type**, a name and typed **parameters**; `void` means "nothing".
- The compiler must see a **prototype** or the definition before the first call.
- A **header** such as `math.h` is a collection of prototypes.
- Arguments are **passed by value**: the function works on copies.
- **Arrays are not copied**: a function can change the caller's array, and needs the length as a separate argument.
- **Local** variables belong to one call; **global** variables exist once for the whole program.


---

**Next:** [Lesson 07: Pointers](../07-pointers/README.md), where a function finally gets to change its caller's variables.

*© Ioannis Tsioulis. *C for Concurrency*. Prepared for educational use.*
