# 42 Common Core

*A 42 Vienna project collection by megardes.*

All my projects from the **42 Common Core**, the C/Unix part of the 42 curriculum, collected in one repository. Most are in folders here. The larger projects that have their own repositories are linked as Git submodules.

## Projects

| Project | What it is | Highlights |
|---|---|---|
| [`libft`](libft) | My own C standard library | Re-implementations of `libc` string, memory and conversion functions plus a linked-list API. Reused by most later projects. |
| [`ft_printf`](ft_printf) | A `printf` clone | Variadic arguments; supports `%c %s %p %d %i %u %x %X %%`. |
| [`get_next_line`](get_next_line) · [`gnl_2`](gnl_2) | Read a file one line at a time | Static buffers, any `BUFFER_SIZE`. The bonus version reads from several file descriptors at once. `gnl_2` is a second, rewritten version. |
| [`pipex`](pipex) | Shell pipes in C | Reproduces `< infile cmd1 \| cmd2 > outfile` with `pipe`, `fork`, `dup2` and `execve`. |
| [`minitalk`](minitalk) | Client/server messaging over signals | The client sends a string bit by bit using only `SIGUSR1` / `SIGUSR2`, and the server rebuilds and prints it. Signals are handled with `sigaction`. |
| [`push_swap`](push_swap) | Sort with two stacks and a limited instruction set | Keeps the longest increasing subsequence in stack A and moves the rest back in a low-cost order, to minimise the number of operations. |
| [`so_long`](so_long) | A small 2D top-down game | Built with MiniLibX: map parsing and validation (`.ber` files), a flood-fill check that the map can be solved, collectibles and an exit. The bonus version is in `srcs_bonus`. |
| [`fract-ol`](fractol) | Fractal explorer | Renders **Mandelbrot** and **Julia** sets with MiniLibX, with zoom and navigation. |
| [`minishell`](https://github.com/mehrasmeydani/minishell) | A bash-like shell *(submodule)* | Parsing, pipes, redirections, heredocs, expansions, signals and built-ins. |
| [`philo`](https://github.com/mehrasmeydani/philo) | Dining philosophers *(submodule)* | Threads, mutexes, deadlock avoidance and precise timing. |
| [`cpp`](https://github.com/mehrasmeydani/42_CPP_modules) | C++ modules 00–09 *(submodule)* | From OOP basics to templates, the STL and Ford-Johnson sort. |

The later Common Core projects (cub3D, Inception, Webserv and ft_transcendence) have their own repositories. They're linked from [my profile](https://github.com/mehrasmeydani).

## Cloning

Clone with the submodules included:

```bash
git clone --recurse-submodules https://github.com/mehrasmeydani/common_core.git
```

If you've already cloned without them:

```bash
git submodule update --init --recursive
```

## Building

Each project builds on its own with `make`:

```bash
cd push_swap && make
./push_swap 3 2 5 1 4
```

All C projects compile with `cc -Wall -Wextra -Werror` and follow the 42 Norm.
