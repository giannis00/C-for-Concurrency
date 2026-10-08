#!/usr/bin/env python3
"""Build the lesson READMEs and .c files from tools/src/*.md, and test every program.

Usage (from anywhere, needs gcc):  python3 tools/build.py        all lessons
                                   python3 tools/build.py 04 07  some lessons
Edit the sources in tools/src, never the generated lesson folders.

Fence attributes (after ```c):
  file=PATH      write the block to PATH inside the lesson folder and caption it
  check          compile and run, but do not write a file (quiz snippets)
  fail           the block must NOT compile (spot-the-bug snippets)
  norun          compile only
  stdin="a\\nb"  lines typed by the user when the program runs
A line `@@output` is replaced by the real output of the previous runnable block.
"""
import json, os, pty, re, select, shlex, shutil, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
SRC, OUT = os.path.join(HERE, "src"), os.path.dirname(HERE)
COURSE = json.load(open(os.path.join(SRC, "course.json")))
STRICT = ["-std=c11", "-Wall", "-Wextra", "-pedantic", "-Wvla", "-Werror",
          "-Wno-implicit-fallthrough"]
SAN = ["-g", "-fsanitize=address,undefined", "-fno-sanitize-recover=all"]
failures, counts = [], {"files": 0, "checks": 0, "fail": 0, "outputs": 0}


def compile_c(code, exe, extra):
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write(code)
    r = subprocess.run(["gcc", *STRICT, *extra, f.name, "-o", exe, "-lm"],
                       capture_output=True, text=True)
    os.unlink(f.name)
    return r


def transcript(exe, lines):
    """Run in a pseudo-terminal so typed input is echoed like a real session."""
    pid, fd = pty.fork()
    if pid == 0:
        os.execv(exe, [exe])
    out, pending = b"", list(lines)
    while True:
        ready, _, _ = select.select([fd], [], [], 0.4)
        if ready:
            try:
                data = os.read(fd, 4096)
            except OSError:
                break
            if not data:
                break
            out += data
        elif pending:
            os.write(fd, (pending.pop(0) + "\n").encode())
        else:
            # idle with nothing left to type: is the program finished?
            done, _ = os.waitpid(pid, os.WNOHANG)
            if done:
                break
    try:
        os.waitpid(pid, 0)
    except ChildProcessError:
        pass
    os.close(fd)
    return out.decode().replace("\r\n", "\n")


def handle_block(attrs, code, where, tmp):
    """Compile and run one block. Returns the transcript (or None)."""
    exe = os.path.join(tmp, "prog")
    if "fail" in attrs:
        counts["fail"] += 1
        if compile_c(code, exe, []).returncode == 0:
            failures.append(f"{where}: marked fail but it compiles")
        return None
    r = compile_c(code, exe + "_san", SAN)
    if r.returncode != 0:
        failures.append(f"{where}: does not compile\n{r.stderr}")
        return None
    r2 = subprocess.run(["gcc", "-std=c99", "-O2", "-x", "c", "-", "-o", exe, "-lm"],
                        input=code, capture_output=True, text=True)
    if r2.returncode != 0:
        failures.append(f"{where}: c99 build failed\n{r2.stderr}")
        return None
    if "norun" in attrs:
        return None
    lines = attrs.get("stdin", "").split("\\n") if "stdin" in attrs else []
    try:
        r = subprocess.run([exe + "_san"], input="\n".join(lines) + "\n",
                           capture_output=True, text=True, timeout=10)
    except subprocess.TimeoutExpired:
        failures.append(f"{where}: timeout")
        return None
    want = int(attrs.get("exit", 0))
    if r.returncode != want or r.stderr.strip():
        failures.append(f"{where}: exit {r.returncode}\n{r.stderr[:1500]}")
        return None
    return transcript(exe, lines)


def build_lesson(idx, lesson, tmp):
    n, total = idx + 1, len(COURSE["lessons"])
    folder = os.path.join(OUT, lesson["folder"])
    os.makedirs(folder, exist_ok=True)
    src = open(os.path.join(SRC, lesson["folder"] + ".md")).read().split("\n")
    out = [f"# 📘 Lesson {n:02d}: {lesson['title']}",
           f"### Course: *{COURSE['title']}*",
           f"**Instructor:** {COURSE['instructor']}  ",
           f"*{COURSE['part']} · Lesson {n} of {total}*", "",
           "[⬅ Course home](../README.md) · [How to run the code](../SETUP.md) · "
           "[Online C compiler](https://www.onlinegdb.com/online_c_compiler)", "", "---", ""]
    i, last, last_attrs = 0, None, {}
    while i < len(src):
        line = src[i]
        m = re.match(r"^```c\s+(\S.*)$", line)
        if m:
            attrs = {}
            for tok in shlex.split(m.group(1)):
                k, _, v = tok.partition("=")
                attrs[k] = v
            j = i + 1
            while src[j] != "```":
                j += 1
            code = "\n".join(src[i + 1:j]) + "\n"
            where = f"{lesson['folder']} line {i + 1} ({attrs.get('file', 'snippet')})"
            last, last_attrs = handle_block(attrs, code, where, tmp), attrs
            if "file" in attrs:
                path = os.path.join(folder, attrs["file"])
                os.makedirs(os.path.dirname(path), exist_ok=True)
                if os.path.exists(path) and path in written:
                    failures.append(f"{where}: duplicate file")
                written.add(path)
                open(path, "w").write(code)
                counts["files"] += 1
                out += [f"📄 [`{attrs['file']}`]({attrs['file']})", ""]
            elif "fail" not in attrs:
                counts["checks"] += 1
            out += ["```c", *src[i + 1:j], "```"]
            i = j + 1
            continue
        if line.strip() == "@@output":
            if last is None:
                failures.append(f"{lesson['folder']} line {i + 1}: @@output without a run")
                last = ""
            counts["outputs"] += 1
            typed = last_attrs.get("stdin")
            label = "**Example run**" if typed is not None else "**Output**"
            out += [label, "", "```text", *last.rstrip("\n").split("\n"), "```"]
            i += 1
            continue
        if re.match(r"^```c\s*$", line):
            pass  # plain fence: shown but not tested (fragments, deliberate bugs)
        out.append(line)
        i += 1
    out += ["", "---", ""]
    if n < total:
        nxt = COURSE["lessons"][n]
        out.append(f"**Next:** [Lesson {n + 1:02d}: {nxt['title']}](../{nxt['folder']}/README.md), "
                   f"{lesson['next']}")
    else:
        out.append(lesson["next"])
    out += ["", f"*© {COURSE['instructor']}. *{COURSE['title']}*. Prepared for educational use.*", ""]
    text = "\n".join(out)
    open(os.path.join(folder, "README.md"), "w").write(text)
    words = len(re.sub(r"```.*?```", "", text, flags=re.S).split())
    print(f"  {lesson['folder']}: {words} words of text")


written = set()
only = sys.argv[1:]
for d in os.listdir(OUT) if os.path.isdir(OUT) else []:
    if re.match(r"^\d\d-", d) and not only:
        shutil.rmtree(os.path.join(OUT, d))
with tempfile.TemporaryDirectory() as tmp:
    for idx, lesson in enumerate(COURSE["lessons"]):
        if only and lesson["folder"][:2] not in only:
            continue
        if not os.path.exists(os.path.join(SRC, lesson["folder"] + ".md")):
            print(f"  {lesson['folder']}: (no source yet)")
            continue
        build_lesson(idx, lesson, tmp)
print(counts)
if failures:
    print(f"\n{len(failures)} FAILURES")
    for f in failures:
        print("-", f)
    sys.exit(1)
print("ALL PASS")
