#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_atoi(const char *nstr);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_itoa(int n);
void *ft_memset(void *s, int c, size_t n);
void ft_putchar(char c);
void ft_putnbr(int n);
void ft_putstr(char *s);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcat(char *dest, const char *src, size_t size);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
size_t ft_strlen(const char *s);

#endif
