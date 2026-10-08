# C for Concurrency

A refresher of the C language for students of *Concurrency and Communication (6CM504)*.

**Instructor:** Ioannis Tsioulis

The labs of the module are written in C and use OpenMP and MPI to run programs on several processor cores. They assume that you can already read and write C. These lessons bring the language back, starting from the first program, and point out along the way the parts of C that parallel programs rely on.

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/giannis00/C-for-Concurrency) &nbsp; or copy any example into the [online C compiler](https://www.onlinegdb.com/online_c_compiler).

## How to use these lessons

1. **Read** a lesson here on GitHub: click a lesson in the table below.
2. **Run** the examples. Each one is shown in the lesson and is also a `.c` file in the `examples` folder of that lesson. The quickest way is to copy it into the [online C compiler](https://www.onlinegdb.com/online_c_compiler). [How to run the code](SETUP.md) also covers Visual Studio, Visual Studio Code and GitHub Codespaces.
3. **Check your understanding.** Every lesson has short questions: predict the output, find the mistake. Answer first, then open the hidden answer.
4. **Do the exercises.** Write each program yourself before you open the solution. The solutions are also files in the `solutions` folder.

Change the examples. Break them on purpose and read what the compiler says. That is the fastest way to remember a language.

## Part 1: C refresher

| # | Lesson | What you revise |
| --- | --- | --- |
| 01 | [Hello, C](01-hello-c/README.md) | the structure of a program, compiling and running, `printf`, compiler errors |
| 02 | [Variables, types and input/output](02-variables-and-io/README.md) | `int`, `double`, `float`, `char`, format specifiers, `scanf`, constants |
| 03 | [Operators and decisions](03-operators-and-decisions/README.md) | integer division and remainder, casts, conditions, `if`, `switch` |
| 04 | [Loops](04-loops/README.md) | `while`, `for`, `do`-`while`, `break`, `continue`, nested loops, accumulators |
| 05 | [Arrays](05-arrays/README.md) | indexing, loops over arrays, element-wise operations, 2D arrays, strings |
| 06 | [Functions](06-functions/README.md) | parameters and return values, prototypes, headers, pass by value, scope |
| 07 | [Pointers](07-pointers/README.md) | addresses, `*` and `&`, pointer parameters, pointers and arrays, `NULL` |
| 08 | [Dynamic memory](08-dynamic-memory/README.md) | stack and heap, `malloc`, `free`, `calloc`, `realloc`, large arrays |
| 09 | [Structs](09-structs/README.md) | `struct`, `typedef`, `->`, structs with dynamic memory, describing a task |

If you are short of time, lessons 04 to 08 matter most for the labs: loops, arrays, functions, pointers and memory.

## What comes next

Planned for this repository, after the refresher:

- **Part 2: OpenMP.** Threads, parallel loops, shared and private data, race conditions, synchronisation.
- **Part 3: MPI.** Processes that cooperate by sending messages.

## What is in each lesson folder

```text
04-loops/
    README.md      the lesson: explanations, questions, exercises with hidden solutions
    examples/      every example of the lesson as a .c file
    solutions/     the solution of every exercise as a .c file
```

Every example and solution in this repository was compiled with `gcc` with warnings switched on, and run.

---

*© Ioannis Tsioulis. *C for Concurrency*. Prepared for educational use.*
