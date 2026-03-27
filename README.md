# ft_printf

A re-implementation of the C `printf` function, based on the 42 School ft_printf project.

## Context

I'm not a 42 School student, but I follow parts of their curriculum on my own time as a personal learning path to deepen my understanding of the C programming language.

## What is ft_printf?

`ft_printf` is one of the core projects of the 42 cursus. The goal is to recode the standard `printf` function from scratch — parsing a format string, handling variadic arguments, and dispatching to the correct output logic for each conversion specifier. It forces you to understand what's actually happening under the hood every time you call `printf`.

## What I learned

* How variadic functions work in C using `va_list`, `va_start`, `va_arg`, and `va_end`
* Parsing format strings manually, character by character
* Handling multiple conversion specifiers with clean dispatch logic
* Writing output functions without relying on `printf` itself
* Managing edge cases like `NULL` pointers, negative numbers, and hex formatting

## Supported conversions

| Specifier | Description |
|-----------|-------------|
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address (hexadecimal) |
| `%d` | Decimal integer |
| `%i` | Integer |
| `%u` | Unsigned decimal integer |
| `%x` | Hexadecimal integer (lowercase) |
| `%X` | Hexadecimal integer (uppercase) |
| `%%` | Literal percent sign |

## Project structure

```
ft_printf/
├── ft_printf.c        # Entry point — format string parser and dispatcher
├── ft_printf_utils.c  # Conversion handlers (char, string, int, hex, pointer…)
├── ft_printf.h        # Header with prototypes
└── Makefile           # Builds the static library (libftprintf.a)
```

## Build

```
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + make
```

## Notes

This project is done purely for learning purposes, following the 42 cursus as a self-study resource. I am not affiliated with 42 School.
