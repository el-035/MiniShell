# Minishell

Minishell is a small Unix shell developed as a group project for the 42
curriculum. It recreates core Bash behavior while exploring process creation,
file descriptors, pipes, signals, parsing, and environment management.

## Team

- `efittant` — parsing
- `apchelni` — execution

## Features

- Interactive prompt and command history
- External commands resolved through `PATH`
- Pipes and multiple-command pipelines
- Input, output, append, and heredoc redirections (`<`, `>`, `>>`, `<<`)
- Single and double quotes
- Environment-variable and `$?` expansion
- Interactive signal handling
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`

## Build

The project requires a C compiler, `make`, and GNU Readline. On Debian or
Ubuntu:

```sh
sudo apt install build-essential libreadline-dev
```

Build from the repository root:

```sh
make
```

## Usage

```sh
./minishell
```

Example:

```text
Minishell: echo "Hello, $USER"
Hello, el
Minishell: cat input.txt | grep minishell > results.txt
Minishell: echo $?
0
Minishell: exit
exit
```

Use `make clean`, `make fclean`, or `make re` to clean or rebuild the project.
