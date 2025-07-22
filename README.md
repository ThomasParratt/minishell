# Minishell

_As beautiful as a shell._

## 📜 Project Description

Minishell is a simplified implementation of a Unix shell written in C. It replicates basic shell functionalities including command parsing, execution with pipes and redirections, built-in commands, environment variable management, and signal handling.

This project was developed as part of the 42 school curriculum to deepen understanding of process control, system calls, and memory management in C.

---

## 🚀 Features

- Interactive prompt
- Working command history (using `readline`)
- Command execution via absolute, relative, or PATH-based binaries
- Single quotes (`'`) prevent interpretation of meta-characters
- Double quotes (`"`) prevent interpretation except for `$` expansion
- Environment variable expansion (`$VAR`)
- Exit status expansion (`$?`)
- Pipes (`|`)
- Redirections:
  - `<` input redirection
  - `>` output redirection
  - `>>` output append redirection
  - `<<` here-document (without adding to history)
- Signal handling:
  - `Ctrl-C` displays a new prompt
  - `Ctrl-D` exits the shell
  - `Ctrl-\` does nothing
- Built-in commands:
  - `echo` (with `-n`)
  - `cd` (absolute or relative path)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## ⚙️ Usage

### Clone the repository

```bash
git clone https://github.com/ThomasParratt/minishell
cd minishell

### Compile

```bash
make

### Run

```bash
./minishell

### Clean object files

```bash
make clean

### Full clean (including executable)

```bash
make fclean

### Recompile

```bash
make re


