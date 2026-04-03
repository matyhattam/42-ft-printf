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
  int is_neg;
  char specifier;
} t_format;

// ft_printf_utils
char *char_to_str(int c);
t_format *create_struct();
void ft_rev_str(char *s);
void set_flags(t_format *format, const char *conv_spec);
int parse_w_p(int *fmt_field, const char *conv_spec);
char *ft_to_hex(unsigned long x);
void to_upper(char *hex);
char *u_to_str(unsigned int u);

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
int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(char *s);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcat(char *dest, const char *src, size_t size);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
size_t ft_strlen(const char *s);

#endif
