#include "ft_printf.h"

typedef struct s_format {
  int left_justify;
  int force_sign;
  int sign_space;
  int zero_padding;
  int alternate_form;
  int width;
  int precision;
  int has_precision;
  char specifier;
} t_format;

t_format *create_struct() { return (ft_calloc(1, sizeof(t_format))); }

void set_flags(t_format *format, const char *specifier) {
  if (*specifier == '-')
    format->left_justify = 1;
  else if (*specifier == '+')
    format->force_sign = 1;
  else if (*specifier == ' ')
    format->sign_space = 1;
  else if (*specifier == '0')
    format->zero_padding = 1;
  else if (*specifier == '#')
    format->alternate_form = 1;
}

void set_precision(t_format *format, const char *specifer) {
  format->has_precision = 1;
  format->precision = ft_atoi(specifer);
}

void parse_specifier(const char *specifier, va_list ap) {
  t_format *format = create_struct();
  int width;

  while (*specifier) {
    if (ft_strchr("-+ 0#", *specifier))
      set_flags(format, specifier);
    else if (ft_strchr("0123456789", *specifier)) {
      width = ft_atoi(specifier);
      printf("%d", width);
    } else if (*specifier == '.') {
      specifier++;
      set_precision(format, specifier);
    } else if (ft_strchr("cspdiuxX%", *specifier)) {
      ft_putnbr(va_arg(ap, int));
      break;
    }
    specifier++;
  }
}

void print_str(const char *s, va_list ap) {
  size_t i = 0;

  while (s[i] != '\0') {
    if (s[i] == '%') {
      i++;
      parse_specifier(&s[i], ap);
      i++;
    }
    ft_putchar(s[i]);
    i++;
  }
}

int ft_printf(const char *s, ...) {
  va_list ap;
  int count;

  va_start(ap, s);
  print_str(s, ap);
  va_end(ap);

  return (count);
}

int main(void) {
  // char *str = "maty est 24 ans";

  ft_printf("maty a %10d ans et son père %d ans", 24, 63);
  // printf("[%+10.5d] [%-10.5s] [%#010x] [% d] [%+d]\n", 42, "hello world",
  // 255,
  //  42, -42);
  // printf("[%d] [%s] [%x] [%d] [%d]\n", 42, "hello world", 255, 42,
  // -42);
}
