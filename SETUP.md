# How to run the code

[⬅ Course home](README.md)

There are four ways to run the examples. Start with the first one: it needs nothing installed.

| Option | Needs | Good for |
| --- | --- | --- |
| [1. Online compiler](#1-online-compiler) | a browser | trying an example in seconds |
| [2. Visual Studio](#2-visual-studio-windows) | Windows, a large installation | the environment used in the labs |
| [3. Visual Studio Code](#3-visual-studio-code) | an editor plus a compiler | Windows, macOS or Linux |
| [4. GitHub Codespaces](#4-github-codespaces) | a browser and a GitHub account | the whole repository, ready to build, in the browser |

## 1. Online compiler

1. Open <https://www.onlinegdb.com/online_c_compiler>.
2. Check that the language selector shows **C**.
3. Open an example here on GitHub, for instance [`01-hello-c/examples/hello.c`](01-hello-c/examples/hello.c), and press the **Copy raw file** button at the top right of the code.
4. Replace the code in the online editor with what you copied and press **Run**.
5. The output appears at the bottom. If the program asks for input, click there and type.

Nothing is saved unless you create an account, so keep your own solutions in files on your computer as well.

## 2. Visual Studio (Windows)

Visual Studio Community is free: <https://visualstudio.microsoft.com/vs/community/>. During installation select the workload **Desktop development with C++**. It includes the C compiler.

1. **Create a new project** and choose **Empty Project** (the C++ one). Give it a name, for example `CRefresher`.
2. In the **Solution Explorer**, right-click **Source Files**, then **Add**, then **New Item**. Choose **C++ File** and type a name that ends in **`.c`**, for example `hello.c`. The `.c` ending tells Visual Studio to compile the file as C.
3. Paste or type the program.
4. Press **Ctrl+F5** (*Start Without Debugging*). A console window shows the output and stays open.

Three things regularly go wrong:

- **Error C4996 about `scanf`.** Put `#define _CRT_SECURE_NO_WARNINGS` on the very first line of the file, before any `#include`. The examples in this course already have it.
- **Two files with a `main` in one project.** A program has exactly one `main`. To run another example, either replace the contents of your file, or right-click the old file and choose **Exclude From Project** before adding the new one.
- **The file ends in `.cpp`.** It is then compiled as C++, and some C code is rejected. Rename it to `.c`.

## 3. Visual Studio Code

Visual Studio Code is an editor, not a compiler. You need both.

1. Install a C compiler:
   - **Windows:** follow <https://code.visualstudio.com/docs/cpp/config-mingw> to install `gcc`.
   - **macOS:** run `xcode-select --install` in the Terminal.
   - **Linux (Ubuntu):** run `sudo apt install build-essential`.
2. Install Visual Studio Code and its **C/C++** extension. The overview is at <https://code.visualstudio.com/docs/languages/cpp>.
3. Download this repository (green **Code** button, then **Download ZIP**) or clone it, and open the folder in Visual Studio Code.
4. Open a terminal inside Visual Studio Code (**Terminal**, then **New Terminal**), then build and run:

```text
cd 01-hello-c/examples
gcc hello.c -o hello
./hello
```

In the Windows PowerShell terminal the last line is `.\hello.exe`.

Useful additions to the `gcc` command:

| Option | Effect |
| --- | --- |
| `-Wall -Wextra` | switch on the compiler warnings; read them, they are usually right |
| `-lm` | needed at the end of the command when the program uses `math.h` (Linux) |
| `-g` | include information for the debugger |

On Linux and macOS, and in a codespace, the command `make` in the top folder of the repository builds every example and solution into a folder called `build`.

## 4. GitHub Codespaces

A codespace is Visual Studio Code running in your browser, on a machine in the cloud that already has `gcc` installed and this repository opened.

1. Sign in to GitHub.
2. Press the **Open in GitHub Codespaces** button on the [course home](README.md), then **Create codespace**. The first start takes a minute or two.
3. Use the terminal at the bottom exactly as in option 3:

```text
cd 01-hello-c/examples
gcc hello.c -o hello
./hello
```

GitHub gives personal accounts a free monthly allowance of codespace time. Stop the codespace when you finish (<https://github.com/codespaces>), so that it does not use the allowance while you are away. Files that you change live in your codespace, not in this repository.
