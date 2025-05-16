# Minishell

A simple Unix shell implemented in C, replicating core functionalities of Bash. This project was developed as part of the 42 school curriculum and focuses on creating a fully functional shell that handles user input, command parsing, and execution.

## 🛠 Features

- Execution of commands with arguments and environment
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Piping (`|`) and redirection (`<`, `>`, `>>`, `<<`)
- Environment variable expansion (`$VAR`)
- Quoting (single and double)
- Signal handling (`Ctrl+C`, `Ctrl+D`)
- Error messages consistent with Bash behavior

## 📦 Dependencies

This project uses the GNU Readline library for interactive input and command history.

More on Readline: [official documentation](https://tiswww.case.edu/php/chet/readline/rltop.html).

Install it (on Fedora) with:

```bash
sudo dnf install readline-devel
```

## ⚙️ Compilation

To build the project, run:

```bash
make
```

## ▶️ Usage

After compilation:

```bash
./minishell
```

This project was developed as part of the 42 school curriculum by laoubaid.
