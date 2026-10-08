## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Declare and initialise variables of type `int`, `double`, `float` and `char`.
- Choose the right type for a value, and explain why `double` is the usual choice for real numbers.
- Print values with `printf` format specifiers, with a chosen width and number of decimals.
- Read values from the keyboard with `scanf`, and explain what the `&` is for.
- Define constants with `#define` and `const`.

> **Prerequisites:** Lesson 01.
>
> 🔭 **Why this lesson matters later:** when you measure how fast a parallel program runs, you store times in `double` variables and print them with `printf`. A wrong format specifier prints nonsense, and it looks like a bug in your parallel code.

## 1. Variables and types

### Intuition first

A variable is a labelled box in memory. In Python a box can hold anything. In C every box has a fixed **type**, chosen when you create it, and the type decides how many bytes the box takes and what you can put in it.

### Formal definition

A **declaration** gives the type and the name: `int count;`. An **initialisation** also gives the first value: `int count = 0;`.

| Type | Holds | Example |
| --- | --- | --- |
| `int` | whole numbers | `int students = 24;` |
| `double` | real numbers, about 15 significant digits | `double average = 61.5;` |
| `float` | real numbers, about 7 significant digits | `float ratio = 0.75f;` |
| `char` | one character | `char grade = 'B';` |

```c file=examples/variables.c
#include <stdio.h>

int main(void)
{
    int    students = 24;       // whole number
    double average  = 61.5;     // real number
    float  ratio    = 0.75f;    // real number with less precision
    char   grade    = 'B';      // one character, in single quotes

    students = students + 1;    // a variable can change its value

    printf("Students: %d\n", students);
    printf("Average:  %.1f\n", average);
    printf("Ratio:    %.2f\n", ratio);
    printf("Grade:    %c\n", grade);
    return 0;
}
```

@@output

### How big is each type?

The operator `sizeof` gives the size of a type in bytes. The exact sizes depend on the machine and the compiler, which is why C lets you ask.

```c file=examples/sizes.c
#include <stdio.h>

int main(void)
{
    printf("char:   %zu byte\n",  sizeof(char));
    printf("int:    %zu bytes\n", sizeof(int));
    printf("float:  %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
    return 0;
}
```

On a typical 64-bit computer:

@@output

### `float` or `double`?

```c file=examples/precision.c
#include <stdio.h>

int main(void)
{
    float  f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;

    printf("float:  %.20f\n", f);
    printf("double: %.20f\n", d);
    return 0;
}
```

@@output

The `float` is already wrong at the eighth decimal. Use `double` unless you have a reason not to.

> ⚠️ **Common pitfalls**
>
> - **Using a variable before giving it a value.** `int x;` followed by `printf("%d", x);` prints whatever happened to be in that memory. C does not set new variables to zero for you.
> - **Single and double quotes.** `'A'` is one `char`. `"A"` is a string. They are different types.
> - **Expecting exact decimals.** `0.1` cannot be stored exactly in binary, so real numbers are close approximations.

## 2. Printing values with `printf`

### Formal definition

A **format specifier** starts with `%` and marks the place where a value is inserted. The values follow the string, in the same order.

| Specifier | Prints | Example | Result |
| --- | --- | --- | --- |
| `%d` | an `int` | `printf("%d", 42)` | `42` |
| `%f` | a `double` or `float`, 6 decimals | `printf("%f", 3.14159)` | `3.141590` |
| `%.2f` | the same, with 2 decimals | `printf("%.2f", 3.14159)` | `3.14` |
| `%c` | a `char` | `printf("%c", 'A')` | `A` |
| `%s` | a string | `printf("%s", "hi")` | `hi` |
| `%zu` | a size, as given by `sizeof` | `printf("%zu", sizeof(int))` | `4` |

A number between `%` and the letter sets the **minimum width**, which is how you line up columns.

```c file=examples/formats.c
#include <stdio.h>

int main(void)
{
    int    threads = 4;
    double seconds = 2.3456789;

    printf("Threads: %d, time: %f s\n", threads, seconds);
    printf("Rounded: %.2f s\n", seconds);

    // %8d and %8.3f pad on the left so that the columns line up
    printf("%8s %8s\n", "threads", "time");
    printf("%8d %8.3f\n", 1, 9.1);
    printf("%8d %8.3f\n", 16, 0.734);
    return 0;
}
```

@@output

## 3. Reading input with `scanf`

### Intuition first

`printf` needs to know the *value* of a variable. `scanf` has to *change* the variable, so it needs to know *where the variable lives* in memory. The `&` in front of a name means "the address of". Lesson 07 explains addresses properly; for now, remember that `scanf` wants `&`.

```c file=examples/age.c stdin="2004"
#define _CRT_SECURE_NO_WARNINGS   // lets scanf build in Visual Studio
#include <stdio.h>

int main(void)
{
    int year;

    printf("What year were you born? ");
    scanf("%d", &year);

    printf("In 2026 you turn %d.\n", 2026 - year);
    return 0;
}
```

@@output

### Formal definition

| To read | Use | Note |
| --- | --- | --- |
| an `int` | `scanf("%d", &n);` | |
| a `double` | `scanf("%lf", &x);` | `%lf`, with a letter l, not `%f` |
| a `float` | `scanf("%f", &f);` | |
| a `char` | `scanf(" %c", &c);` | the space before `%c` skips the Enter left over from the previous input |

Several values can be read in one call. The user separates them with spaces or Enter.

```c file=examples/rectangle.c stdin="4.5 2"
#define _CRT_SECURE_NO_WARNINGS   // lets scanf build in Visual Studio
#include <stdio.h>

int main(void)
{
    double width, height;

    printf("Width and height: ");
    scanf("%lf %lf", &width, &height);

    printf("Area: %.2f\n", width * height);
    return 0;
}
```

@@output

> 🛠️ **Visual Studio and `scanf`.** With its default settings, Visual Studio refuses to build a program that calls `scanf`, with error C4996 ("This function or variable may be unsafe"). The line `#define _CRT_SECURE_NO_WARNINGS` at the very top of the file, before any `#include`, switches that check off. Other compilers ignore the line, so the examples in this course always include it.

> ⚠️ **Common pitfalls**
>
> - **Forgetting the `&`.** `scanf("%d", year);` builds (with a warning) and then usually crashes.
> - **`%f` for a `double` in `scanf`.** `printf` uses `%f` for both `float` and `double`, but `scanf` needs `%lf` for a `double`. With `%f` the variable ends up with a meaningless value.
> - **Putting `\n` at the end of a `scanf` format.** `scanf("%d\n", &n);` keeps waiting for more input. Leave it out.

## 4. Constants

A value that never changes deserves a name. There are two ways to give it one.

```c file=examples/circle.c
#include <stdio.h>

#define PI 3.14159265358979      // the preprocessor replaces PI by this text

int main(void)
{
    const double radius = 3.0;   // a variable that may not be changed

    printf("Perimeter: %.3f\n", 2 * PI * radius);
    printf("Area:      %.3f\n", PI * radius * radius);
    return 0;
}
```

@@output

`#define` has no type, no `=` and no semicolon: before compiling, every `PI` in the file is replaced by the text that follows it. By convention such names are written in capitals. You will see `#define N 1000000` at the top of many programs in this course, to set the size of the problem in one place.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    int a = 5, b = 9;
    a = b;
    b = a;
    printf("%d %d\n", a, b);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`a = b;` overwrites the 5, so it is lost. When `b = a;` runs, `a` already holds 9. An assignment copies a value; it does not exchange two values. Exercise 4 asks you to do the exchange properly.

</details>

**Q2.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    char c = 'A';
    printf("%c %d %c\n", c, c, c + 1);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

A `char` is stored as a small whole number, its character code. `%c` shows the character, `%d` shows the code, and the code after `'A'` belongs to `'B'`.

</details>

**Q3.** Find the two mistakes:

```c
double price;
scanf("%f", price);
```

<details><summary>💡 Show answer</summary>

A `double` is read with `%lf`, and `scanf` needs the address: `scanf("%lf", &price);`.

</details>

**Q4.** What does `printf("%5.1f|%d|\n", 3.14159, 7);` print?

```c check
#include <stdio.h>

int main(void)
{
    printf("%5.1f|%d|\n", 3.14159, 7);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`%5.1f` means one decimal and at least five characters in total, so `3.1` gets two spaces in front of it.

</details>

**Q5.** A program contains `int total;` and later `total = total + 10;` with nothing in between. What is the value of `total` afterwards?

<details><summary>💡 Show answer</summary>

Nobody can say. `total` was never given a first value, so it starts with whatever was in that piece of memory. Write `int total = 0;`.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (temperature)

Ask for a temperature in degrees Celsius and print it in Fahrenheit with one decimal. Use F = C × 1.8 + 32.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex1_temperature.c stdin="30"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double celsius;

    printf("Temperature in Celsius: ");
    scanf("%lf", &celsius);

    printf("%.1f C = %.1f F\n", celsius, celsius * 1.8 + 32);
    return 0;
}
```

</details>

### Exercise 2 (simple interest)

Ask for a principal, a yearly rate in percent and a number of years. Print the simple interest: principal × rate × years / 100.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex2_interest.c stdin="1000 3.5 2"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double principal, rate, years;

    printf("Principal, rate (%%) and years: ");
    scanf("%lf %lf %lf", &principal, &rate, &years);

    printf("Interest: %.2f\n", principal * rate * years / 100);
    return 0;
}
```

</details>

### Exercise 3 (hours)

Store a number of hours in a `double` constant (for example 2.5) and print how many minutes and how many seconds that is.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex3_hours.c
#include <stdio.h>

int main(void)
{
    const double hours = 2.5;

    printf("%.1f hours = %.0f minutes = %.0f seconds\n",
           hours, hours * 60, hours * 3600);
    return 0;
}
```

*`%.0f` prints a real number without decimals.*

</details>

### Exercise 4 (swap)

Read two integers into `a` and `b`, exchange their values, and print them. After the swap `a` must hold what the user typed second.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex4_swap.c stdin="3 8"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int a, b;

    printf("Two integers: ");
    scanf("%d %d", &a, &b);

    int temp = a;   // keep the old a before it is overwritten
    a = b;
    b = temp;

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
```

*The third variable keeps the value that would otherwise be lost, as in Q1.*

</details>

### Exercise 5 (average of three)

Read three real numbers and print their average with two decimals.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex5_average.c stdin="7 8.5 10"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double x, y, z;

    printf("Three numbers: ");
    scanf("%lf %lf %lf", &x, &y, &z);

    printf("Average: %.2f\n", (x + y + z) / 3);
    return 0;
}
```

</details>

### Exercise 6 (a results table, a little harder)

A program ran with 1, 2 and 4 threads and took 12.5, 6.4 and 3.35 seconds. Store the three times in `double` variables and print this table, with the columns lined up by width specifiers and not by typing spaces:

```text
 threads   time (s)
       1     12.500
       2      6.400
       4      3.350
```

<details><summary>💡 Show solution</summary>

```c file=solutions/ex6_table.c
#include <stdio.h>

int main(void)
{
    double t1 = 12.5, t2 = 6.4, t4 = 3.35;

    printf("%8s %10s\n", "threads", "time (s)");
    printf("%8d %10.3f\n", 1, t1);
    printf("%8d %10.3f\n", 2, t2);
    printf("%8d %10.3f\n", 4, t4);
    return 0;
}
```

*You will print tables like this one when you compare running times in the labs.*

</details>

---

## 🔑 Key takeaways

- Every variable has a **type** that is fixed when you declare it: `int`, `double`, `float`, `char`.
- A new variable has **no defined value** until you give it one.
- Prefer **`double`** for real numbers; `float` keeps only about 7 digits.
- `printf` inserts values at **format specifiers**: `%d`, `%f`, `%.2f`, `%c`, `%s`.
- `scanf` needs the **address** of the variable (`&x`), and **`%lf`** for a `double`.
- In Visual Studio, put **`#define _CRT_SECURE_NO_WARNINGS`** on the first line of a file that uses `scanf`.
- Name fixed values with **`#define`** or **`const`**.
