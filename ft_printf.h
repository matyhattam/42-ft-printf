#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_format {
  int alt_form;
  int f_sign;
  int s_space;
  int is_neg;
  int has_precision;
  int precision;
  int width;
  int z_padding;
  int justify;
  char specifier;
} t_format;

// ft_parsing_utils
int parse_fmt(const char *conv_spec, va_list *ap);
char *parse_specs(t_format *fmt, va_list *ap);
int parse_w_p(int *fmt_field, const char *conv_spec);
void set_flags(t_format *format, const char *conv_spec);

// ft_formatting_utils
char *apply_force_sign(char *s, t_format *fmt);
char *apply_precision(t_format *fmt, char *input, size_t input_len);
char *apply_width(t_format *fmt, char *input, size_t input_len);
char *apply_width_c(t_format *fmt, char *c);
char *format_c(int c, t_format *fmt);
char *format_d(int d, t_format *fmt);
char *format_s(char *s, t_format *fmt);
char *format_u(unsigned int u, t_format *fmt);
char *format_x(va_list *ap, t_format *fmt, int is_p);

// ft_printf_utils
char *ft_ctostr(int c);
t_format *create_struct();
void ft_rev_str(char *s);
char *ft_tohex(unsigned long x);
int replace(char **src, char *new);
void to_upper(char *hex);
char *ft_utostr(unsigned int u);

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
