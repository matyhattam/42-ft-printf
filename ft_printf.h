#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_format {
  int justify_left;
  int force_sign;
  int sign_space;
  int zero_padding;
  int alternate_form;
  int width;
  int precision;
  int has_precision;
  char specifier;
} t_format;

// ft_printf_utils
char *char_to_str(char c);
t_format *create_struct();
void ft_rev_str(char *s);
void set_flags(t_format *format, const char *conv_spec);
int str_to_int(int *fmt_field, const char *conv_spec);
char *ft_to_hex(unsigned int x);

// libft
int ft_atoi(const char *nstr);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_itoa(int n);
void *ft_memcpy(void *dest, const void *src, size_t n);
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
