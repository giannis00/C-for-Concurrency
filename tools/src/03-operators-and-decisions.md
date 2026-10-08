## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Use the arithmetic operators, and predict the result of dividing two integers.
- Convert between `int` and `double` with a cast.
- Build conditions with comparison and logical operators.
- Choose between alternatives with `if`, `else if` and `else`.
- Use `switch` for a choice among fixed values, and explain what `break` does there.

> **Prerequisites:** Lessons 01 and 02.
>
> 🔭 **Why this lesson matters later:** splitting work between threads is integer arithmetic. "How many elements does each thread get, and how many are left over?" is answered by `/` and `%`.

## 1. Arithmetic

### Formal definition

| Operator | Meaning | `7 op 2` with integers |
| --- | --- | --- |
| `+` `-` `*` | add, subtract, multiply | `9`, `5`, `14` |
| `/` | divide | `3` (the fractional part is thrown away) |
| `%` | remainder of the division | `1` |

### Intuition first

When both sides of `/` are integers, C gives an integer answer: 7 sweets shared between 2 children is 3 each, with 1 left over. The `3` is `7 / 2` and the `1` is `7 % 2`. If at least one side is a `double`, the division is a real division.

```c file=examples/division.c
#include <stdio.h>

int main(void)
{
    int a = 7, b = 2;

    printf("a / b          = %d\n", a / b);            // integer division
    printf("a %% b          = %d\n", a % b);            // remainder
    printf("7.0 / b        = %.1f\n", 7.0 / b);        // one side is a double
    printf("(double) a / b = %.1f\n", (double) a / b); // cast a first

    double wrong = a / b;   // the division is done with integers, then stored
    printf("wrong          = %.1f\n", wrong);
    return 0;
}
```

@@output

A **cast** such as `(double) a` produces the value of `a` converted to another type, for that one expression. `a` itself stays an `int`.

### Shortcuts

| Short form | Same as |
| --- | --- |
| `x += 5;` | `x = x + 5;` (also `-=`, `*=`, `/=`, `%=`) |
| `x++;` | `x = x + 1;` |
| `x--;` | `x = x - 1;` |

Multiplication, division and remainder are done before addition and subtraction, as in mathematics. When in doubt, add brackets.

> ⚠️ **Common pitfalls**
>
> - **An average that loses its decimals.** `double avg = sum / count;` with two `int` variables gives `3.0`, not `3.5`. Write `(double) sum / count`.
> - **`1 / 2` is `0`.** So `1 / 2 * x` is always zero. Write `0.5 * x` or `x / 2.0`.
> - **Dividing an integer by zero** crashes the program.

## 2. Conditions

### Formal definition

A comparison produces an `int`: `1` when it is true and `0` when it is false. In the other direction, C treats `0` as false and **any other number** as true.

| Operator | Meaning | | Operator | Meaning |
| --- | --- | --- | --- | --- |
| `==` | equal to | | `&&` | and: both must be true |
| `!=` | not equal to | | `\|\|` | or: at least one is true |
| `<` `<=` | less than (or equal) | | `!` | not: turns true into false |
| `>` `>=` | greater than (or equal) | | | |

```c file=examples/conditions.c
#include <stdio.h>

int main(void)
{
    int age = 20;

    printf("%d\n", age >= 18);               // true is 1
    printf("%d\n", age == 21);               // false is 0
    printf("%d\n", age >= 18 && age < 65);   // both parts are true
    printf("%d\n", age < 18 || age >= 65);   // neither part is true
    printf("%d\n", !(age == 21));            // not false
    return 0;
}
```

@@output

`&&` and `||` stop as soon as the answer is known. In `b != 0 && a / b > 2`, the division is not attempted when `b` is zero, because the first part is already false.

## 3. `if`, `else if`, `else`

### Intuition first

At a junction you take one road. An `if` chain tests its conditions from top to bottom and runs the block of the **first** one that is true. The rest are skipped.

```c file=examples/classification.c stdin="64"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int mark;

    printf("Final mark (0-100): ");
    scanf("%d", &mark);

    if (mark < 0 || mark > 100) {
        printf("That is not a valid mark.\n");
    } else if (mark >= 70) {
        printf("First class\n");
    } else if (mark >= 60) {
        printf("Upper second (2:1)\n");
    } else if (mark >= 50) {
        printf("Lower second (2:2)\n");
    } else if (mark >= 40) {
        printf("Third class\n");
    } else {
        printf("Fail\n");
    }
    return 0;
}
```

@@output

The test `mark >= 60` does not need to say "and below 70": the chain only reaches it when `mark >= 70` was false.

For a simple choice between two values there is a compact form, the **conditional operator**: `int larger = (a > b) ? a : b;` reads "if `a > b` then `a`, otherwise `b`".

> ⚠️ **Common pitfalls**
>
> - **`=` instead of `==`.** `if (x = 5)` stores 5 in `x`, and since 5 is not zero the condition is always true. The compiler only warns.
> - **Leaving out the braces.** Without `{ }` only the *next single statement* belongs to the `if`. Always write the braces.
> - **A semicolon after the condition.** `if (x > 0);` ends the `if` at once, and the block below it always runs.
> - **`0 < x < 10`.** This compiles but does not mean what it means in mathematics. Write `x > 0 && x < 10`.

## 4. `switch`

### Formal definition

`switch` compares one integer or character with a list of constant values and jumps to the matching `case`. Execution then continues downwards until it meets a `break`. `default` catches every value that has no `case`.

```c file=examples/calculator.c stdin="12 / 5"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double a, b;
    char op;

    printf("Calculation (for example 3 * 4): ");
    scanf("%lf %c %lf", &a, &op, &b);

    switch (op) {
        case '+':
            printf("%.2f\n", a + b);
            break;
        case '-':
            printf("%.2f\n", a - b);
            break;
        case '*':
            printf("%.2f\n", a * b);
            break;
        case '/':
            if (b == 0) {
                printf("Cannot divide by zero.\n");
            } else {
                printf("%.2f\n", a / b);
            }
            break;
        default:
            printf("Unknown operator '%c'.\n", op);
    }
    return 0;
}
```

@@output

Use `switch` when one value is compared with fixed alternatives (a menu choice, an operator). Use `if` for ranges such as `mark >= 60`, which `switch` cannot express.

---

## 🧠 Check your understanding

**Q1.** What does this program print?

```c check
#include <stdio.h>

int main(void)
{
    printf("%d %d %.2f\n", 9 / 4, 9 % 4, 9 / 4.0);
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

`9 / 4` is an integer division, `9 % 4` is its remainder, and `9 / 4.0` is a real division because one side is a `double`.

</details>

**Q2.** Ten array elements are shared between 4 threads. With integer arithmetic, how many elements does each thread get, and how many are left over? Which expressions give these two numbers?

<details><summary>💡 Show answer</summary>

`10 / 4` is 2 elements each, and `10 % 4` is 2 left over. Any scheme that splits a loop between threads has to decide who takes the leftovers.

</details>

**Q3.** What does this program print when `n` is 2? The `break` statements are missing on purpose.

```c check
#include <stdio.h>

int main(void)
{
    int n = 2;

    switch (n) {
        case 1:
            printf("one ");
        case 2:
            printf("two ");
        case 3:
            printf("three ");
        default:
            printf("many");
    }
    printf("\n");
    return 0;
}
```

<details><summary>💡 Show answer</summary>

@@output

Execution jumps to `case 2` and then **falls through** every case below it, because nothing tells it to stop. Each case normally ends with `break`.

</details>

**Q4.** `score` is 30. What does this fragment print?

```c
if (score >= 40)
    printf("Pass. ");
    printf("Well done!\n");
```

<details><summary>💡 Show answer</summary>

`Well done!` Only the first `printf` belongs to the `if`. The indentation of the second one fools the reader, not the compiler. With braces the mistake could not happen.

</details>

**Q5.** `x` is 10. What is printed, and what is the value of `x` afterwards?

```c
if (x = 5) {
    printf("five\n");
}
```

<details><summary>💡 Show answer</summary>

It prints `five`, and `x` is now 5. A single `=` is an assignment. Its value, 5, is not zero, so it counts as true. The comparison is `x == 5`.

</details>

---

## ✏️ Exercises

Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (even or odd)

Read an integer and print whether it is even or odd.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex1_even_odd.c stdin="17"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int n;

    printf("An integer: ");
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("%d is even.\n", n);
    } else {
        printf("%d is odd.\n", n);
    }
    return 0;
}
```

</details>

### Exercise 2 (largest of three)

Read three integers and print the largest.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex2_largest.c stdin="4 19 7"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int a, b, c;

    printf("Three integers: ");
    scanf("%d %d %d", &a, &b, &c);

    int largest = a;          // assume the first, then let the others challenge it
    if (b > largest) {
        largest = b;
    }
    if (c > largest) {
        largest = c;
    }
    printf("Largest: %d\n", largest);
    return 0;
}
```

*The same idea, "keep the best so far", finds the maximum of an array in Lesson 05.*

</details>

### Exercise 3 (leap year)

Read a year and say whether it is a leap year. A year is a leap year if it is divisible by 4, except that years divisible by 100 are not, unless they are also divisible by 400. Test with 2024, 1900 and 2000.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex3_leap_year.c stdin="1900"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int year;

    printf("Year: ");
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }
    return 0;
}
```

</details>

### Exercise 4 (BMI)

Read a weight in kilograms and a height in metres. Compute BMI = weight / height², print it with one decimal, and print the category: below 18.5 underweight, below 25 normal weight, below 30 overweight, otherwise obese.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex4_bmi.c stdin="70 1.75"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    double weight, height;

    printf("Weight (kg) and height (m): ");
    scanf("%lf %lf", &weight, &height);

    double bmi = weight / (height * height);
    printf("BMI: %.1f\n", bmi);

    if (bmi < 18.5) {
        printf("Underweight\n");
    } else if (bmi < 25) {
        printf("Normal weight\n");
    } else if (bmi < 30) {
        printf("Overweight\n");
    } else {
        printf("Obese\n");
    }
    return 0;
}
```

</details>

### Exercise 5 (vowel or consonant)

Read a lower-case letter and print whether it is a vowel or a consonant. Use `switch`, and let several `case` labels share one block.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex5_vowel.c stdin="e"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    char letter;

    printf("A lower-case letter: ");
    scanf(" %c", &letter);

    switch (letter) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            printf("'%c' is a vowel.\n", letter);
            break;
        default:
            printf("'%c' is a consonant.\n", letter);
    }
    return 0;
}
```

*Here falling through is useful: five labels lead to the same statements.*

</details>

### Exercise 6 (hours, minutes, seconds; a little harder)

Read a duration in whole seconds and print it as hours, minutes and seconds. For example 3725 becomes `1 h 2 min 5 s`. Use only `/` and `%`.

<details><summary>💡 Show solution</summary>

```c file=solutions/ex6_duration.c stdin="3725"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int total;

    printf("Seconds: ");
    scanf("%d", &total);

    int hours   = total / 3600;
    int minutes = (total % 3600) / 60;   // what is left after the full hours
    int seconds = total % 60;

    printf("%d h %d min %d s\n", hours, minutes, seconds);
    return 0;
}
```

</details>

---

## 🔑 Key takeaways

- Dividing two **integers** gives an integer; **`%`** gives the remainder.
- A **cast**, `(double) a`, forces a real division.
- Comparisons give **1 or 0**; anything that is not zero counts as true.
- **`==`** compares, **`=`** assigns.
- An `if` chain runs the **first** block whose condition is true. Always use braces.
- In a `switch`, every case needs a **`break`**, unless you want it to fall through.
