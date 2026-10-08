# 📘 Lesson 01: Hello, C
### Course: *C for Concurrency*
**Instructor:** Ioannis Tsioulis  
*Part 1: C refresher · Lesson 1 of 9*

[⬅ Course home](../README.md) · [How to run the code](../SETUP.md) · [Online C compiler](https://www.onlinegdb.com/online_c_compiler)

---

## 🎯 Learning objectives

By the end of this lesson you will be able to:

- Explain what every line of a minimal C program does.
- Describe the steps that turn a `.c` file into a program you can run.
- Compile and run a program online, in Visual Studio and from a terminal.
- Print text with `printf`, including new lines, tabs and quotation marks.
- Write comments, and read the most common compiler error messages.

> **Prerequisites:** none. You have programmed before in some language; this lesson reminds you how C does it.
>
> 🔭 **Why this lesson matters later:** in the parallel programming labs you will switch compiler options on (for example the one that enables OpenMP). That only makes sense once you know what the compiler does.

## 1. Your first program

### Intuition first

A C program is a text file with a list of instructions. The computer cannot run text, so a program called the **compiler** translates the file into machine code first. Execution always starts at a function called `main`.

Here is the whole program. Read it, then run it.

📄 [`examples/hello.c`](examples/hello.c)

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

**Output**

```text
Hello, World!
```

### Line by line

| Line | What it does |
| --- | --- |
| `#include <stdio.h>` | Brings in the declarations of the standard input/output functions. Without it the compiler does not know what `printf` is. |
| `int main(void)` | Defines the function where execution begins. `int` says it returns a whole number; `void` says it takes no arguments. |
| `{` and `}` | Mark the beginning and the end of the body of `main`. |
| `printf("Hello, World!\n");` | Writes the text between the double quotes to the screen. `\n` moves to a new line. |
| `return 0;` | Ends `main` and reports success to the operating system. Any other number means that something went wrong. |

Two rules catch almost everybody at the start:

- Every statement ends with a semicolon `;`.
- C is case sensitive: `Main`, `Printf` and `Return` are not the same as `main`, `printf` and `return`.

## 2. From source code to a running program

### Intuition first

Python reads your file and executes it line by line. C works in two separate moments: first you **build** the program, then you **run** the result. If the build fails, nothing runs at all.

### Formal definition

| Step | Input | Output | Typical problem found here |
| --- | --- | --- | --- |
| **Preprocessing** | `hello.c` | the same file with every `#include` replaced by the contents of that header | a header file that does not exist |
| **Compiling** | preprocessed code | machine code for this file (an *object file*) | syntax errors, wrong types |
| **Linking** | object files and libraries | one executable program | a function that was declared but never defined |
| **Running** | the executable | your output | crashes, wrong results |

From a terminal, with the `gcc` compiler, all the build steps happen in one command:

```text
gcc hello.c -o hello     build: creates a program called "hello"
./hello                  run it (Linux, macOS)
hello.exe                run it (Windows)
```

In Visual Studio the same steps hide behind **Build** and **Start Without Debugging** (`Ctrl+F5`). In an online compiler they hide behind the **Run** button. The page [How to run the code](../SETUP.md) shows each option step by step.

### Why it matters

Errors come from different steps, and knowing which step complained tells you where to look. A message that starts with `error:` and a line number comes from the compiler. A program that builds but prints the wrong answer has a logic mistake that only you can find.

## 3. Printing with `printf`

### Formal definition

`printf` prints the characters of its string exactly as written, except for **escape sequences**, which start with a backslash:

| You write | You get |
| --- | --- |
| `\n` | a new line |
| `\t` | a tab (jumps to the next column stop) |
| `\"` | a double quote |
| `\\` | one backslash |
| `%%` | one percent sign |

`printf` does **not** add a new line for you. Two calls without `\n` print on the same line.

📄 [`examples/escapes.c`](examples/escapes.c)

```c
#include <stdio.h>

int main(void)
{
    printf("One ");
    printf("line.\n");                    // still the first line
    printf("Name:\tAda\nRole:\tStudent\n");
    printf("She said \"hello\".\n");
    printf("Progress: 100%%\n");
    return 0;
}
```

**Output**

```text
One line.
Name:	Ada
Role:	Student
She said "hello".
Progress: 100%
```

## 4. Comments

Comments are notes for humans. The compiler ignores them.

📄 [`examples/comments.c`](examples/comments.c)

```c
#include <stdio.h>

/* A comment between these marks
   can cover several lines. */
int main(void)
{
    // A comment after two slashes ends at the end of the line.
    printf("Comments do not print.\n");   // it can follow a statement
    return 0;
}
```

**Output**

```text
Comments do not print.
```

A useful comment says *why* the code does something. The code already says *what* it does.

## 5. Reading compiler errors

### Intuition first

The compiler stops at the first place where the text no longer makes sense. That place is often *just after* the real mistake.

This program is missing one semicolon:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n")
    return 0;
}
```

`gcc` answers with a message like this:

```text
hello.c: In function 'main':
hello.c:5:30: error: expected ';' before 'return'
```

Read it from left to right: the file, the line (5), the column (30), and what the compiler expected. The semicolon is missing at the end of line 5, although the compiler only noticed when it reached `return` on line 6.

> ⚠️ **Common pitfalls**
>
> - **Fixing the last error first.** One mistake can produce ten messages. Fix the first one, build again, and the rest often disappear.
> - **Curly quotes.** Code copied from a slide or a PDF may contain `“ ”` instead of `" "`. The compiler rejects them. Type the quotes yourself.
> - **Forgetting to build again.** If you run an old executable, your change seems to have no effect.
> - **Saving the file as `.cpp`.** Visual Studio then compiles it as C++. In this course the files end in `.c`.

---

## 🧠 Check your understanding

Answer in your head or on paper first, then open the answer.

**Q1.** What does this program print, and on how many lines?

```c
#include <stdio.h>

int main(void)
{
    printf("A");
    printf("B\n");
    printf("C\n\nD\n");
    return 0;
}
```

<details><summary>💡 Show answer</summary>

**Output**

```text
AB
C

D
```

Four lines, one of them empty. `A` and `B` share a line because the first `printf` has no `\n`. The two `\n` in a row after `C` leave an empty line.

</details>

**Q2.** A program builds without errors but prints the wrong result. Which step found the problem: preprocessing, compiling, linking or running?

<details><summary>💡 Show answer</summary>

Running. The build steps only check that the text is valid C. They cannot know what you *meant* the program to do.

</details>

**Q3.** What is wrong with `#include <stdio.h>;` and with `Printf("Hi\n");`?

<details><summary>💡 Show answer</summary>

`#include` is a preprocessor directive, not a statement, so it takes no semicolon. `Printf` with a capital P is a different name from `printf`, and no such function exists.

</details>

**Q4.** What does `return 0;` in `main` tell the operating system? What would `return 1;` tell it?

<details><summary>💡 Show answer</summary>

`0` means that the program finished successfully. Any other value signals a failure. Scripts and tools that start your program can read this number.

</details>

**Q5.** True or false: if you delete the line `#include <stdio.h>` from the first program, it still builds cleanly.

<details><summary>💡 Show answer</summary>

False. `printf` is declared in `stdio.h`. Without the include, the compiler meets a name it has never seen. Recent versions of `gcc` stop with an error; older versions and some other compilers print a warning and guess what you meant.

</details>

---

## ✏️ Exercises

Write each program yourself before you look at the solution. Every solution is also a file in the [`solutions`](solutions) folder.

### Exercise 1 (student card)

Print the following card, with your own details. Use tabs to line up the second column.

```text
*** Student Information ***
Name:   Ada Lovelace
ID:     2025000001
Course: C for Concurrency
***************************
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex1_student_card.c`](solutions/ex1_student_card.c)

```c
#include <stdio.h>

int main(void)
{
    printf("*** Student Information ***\n");
    printf("Name:\tAda Lovelace\n");
    printf("ID:\t2025000001\n");
    printf("Course:\tC for Concurrency\n");
    printf("***************************\n");
    return 0;
}
```

*Each label is shorter than one tab stop, so a single `\t` lines up the values.*

</details>

### Exercise 2 (one call, three lines)

Print these three lines with a **single** `printf` call:

```text
Threads
Processes
Messages
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex2_one_call.c`](solutions/ex2_one_call.c)

```c
#include <stdio.h>

int main(void)
{
    printf("Threads\nProcesses\nMessages\n");
    return 0;
}
```

</details>

### Exercise 3 (quotes and backslashes)

Print exactly this line, including the quotation marks and the backslashes:

```text
Save "lab1.c" in C:\work\labs
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex3_quotes.c`](solutions/ex3_quotes.c)

```c
#include <stdio.h>

int main(void)
{
    printf("Save \"lab1.c\" in C:\\work\\labs\n");
    return 0;
}
```

*A backslash starts an escape sequence, so a real backslash is written twice.*

</details>

### Exercise 4 (a box)

Print this box using only `printf`:

```text
+----------------+
|                |
|  Welcome to C  |
|                |
+----------------+
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex4_box.c`](solutions/ex4_box.c)

```c
#include <stdio.h>

int main(void)
{
    printf("+----------------+\n");
    printf("|                |\n");
    printf("|  Welcome to C  |\n");
    printf("|                |\n");
    printf("+----------------+\n");
    return 0;
}
```

</details>

### Exercise 5 (fix the program, a little harder)

This program has **four** mistakes. Find them by reading, then check with the compiler.

```c
#include <stdio.h>

int Main(void)
{
    printf("Compiling is step one.\n")
    printf('Running is step two.\n');
    return 0
}
```

<details><summary>💡 Show solution</summary>

📄 [`solutions/ex5_fixed.c`](solutions/ex5_fixed.c)

```c
#include <stdio.h>

int main(void)
{
    printf("Compiling is step one.\n");
    printf("Running is step two.\n");
    return 0;
}
```

*The mistakes: `Main` instead of `main`, a missing semicolon after the first `printf`, single quotes around a string, and a missing semicolon after `return 0`.*

</details>

---

## 🔑 Key takeaways

- A C program starts at **`main`**, and `return 0;` reports success.
- **`#include <stdio.h>`** makes `printf` known to the compiler.
- C is **compiled**: preprocessing, compiling and linking happen before anything runs.
- **`printf`** prints exactly what you give it; `\n` and `\t` are **escape sequences** for a new line and a tab.
- Every statement ends with a **semicolon**, and names are **case sensitive**.
- Fix the **first** compiler error, then build again.


---

**Next:** [Lesson 02: Variables, types and input/output](../02-variables-and-io/README.md), where programs start to remember things and talk to the user.

*© Ioannis Tsioulis. *C for Concurrency*. Prepared for educational use.*
