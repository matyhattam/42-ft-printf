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

void set_flags(t_format *format, const char *conv_spec) {
  if (*conv_spec == '-')
    format->left_justify = 1;
  else if (*conv_spec == '+')
    format->force_sign = 1;
  else if (*conv_spec == ' ')
    format->sign_space = 1;
  else if (*conv_spec == '0')
    format->zero_padding = 1;
  else if (*conv_spec == '#')
    format->alternate_form = 1;
}

void set_precision(t_format *format, const char *conv_spec) {
  format->has_precision = 1;
  format->precision = ft_atoi(conv_spec);
}
void set_specifier(t_format *format, const char *conv_spec) {}

int parse_format(const char *conv_spec, va_list ap) {
  int count = 1;
  t_format *format = create_struct();

  while (*conv_spec) {
    if (ft_strchr("-+ 0#", *conv_spec))
      set_flags(format, conv_spec);
    else if (ft_strchr("0123456789", *conv_spec)) {
      int to_int;
      while (*conv_spec >= '0' && *conv_spec <= '9') {
        to_int = to_int * 10 + *conv_spec - '0';
        conv_spec++;
      }
      format->width = to_int;
    } else if (*conv_spec == '.') {
      conv_spec++;
      count++;
      set_precision(format, conv_spec);
    } else if (ft_strchr("cspdiuxX%", *conv_spec)) {
      ft_putnbr(va_arg(ap, int));
      printf("%d ", format->width);
      return (count);
    }
    conv_spec++;
    count++;
  }

  return (count);
}

void print_str(const char *s, va_list ap) {
  size_t i = 0;

  while (s[i] != '\0') {
    if (s[i] == '%') {
      i++;
      int count = parse_format(&s[i], ap);
      i += count;
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

  ft_printf("maty a %53d ans et son père %d ans.", 24, 63);
  // printf("[%+10.5d] [%-10.5s] [%#010x] [% d] [%+d]\n", 42, "hello world",
  // 255,
  //  42, -42);
  // printf("[%d] [%s] [%x] [%d] [%d]\n", 42, "hello world", 255, 42,
  // -42);
}
