
# Minishell: As Beautiful as a Shell

Minishell is a simple shell created as part of my 1337 (42 Network) studies. It supports basic command execution, pipes, redirections, environment variables, and built-in commands like `cd`, `pwd`, `echo`, and more. It also handles signals (`Ctrl-C`, `Ctrl-D`) and offers a history feature.

## Features
- Command execution based on `PATH` or relative/absolute paths.
- History functionality for command recall.
- Input/output redirections (`<`, `>`, `<<`, `>>`).
- Pipe support (`|` for piping output between commands).
- Environment variable handling (`$VAR` expansion).
- Special handling for `$?` (exit status of the last command).
- Signal handling for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Supports single and double quotes for escaping special characters.

## How to Use
1. Clone the repository.
2. Run `make` to build the shell.
3. Execute the program with `./minishell`.

This project adheres to strict memory management rules, ensuring no leaks in user-defined code, and follows the 42 Norm.
