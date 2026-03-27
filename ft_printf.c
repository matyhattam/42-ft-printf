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

int str_to_int(int *fmt_field, const char *conv_spec) {
  int to_int = 0;
  int offset = 0;
  while (*conv_spec >= '0' && *conv_spec <= '9') {
    to_int = to_int * 10 + *conv_spec - '0';
    offset++;
    conv_spec++;
  }
  *fmt_field = to_int;
  return (offset);
}

char *apply_padding(int padding_len, size_t len, int is_precision) {
  char *s = "";
  if (padding_len >= len) {
    size_t len_pad = padding_len - len;
    s = malloc(len_pad * sizeof(char));
    size_t i = 0;
    while (i < len_pad) {
      s[i] = is_precision ? '0' : ' ';
      i++;
    }
    s[i] = '\0';
  }

  return (s);
}

char *apply_width(int *width, size_t len) {
  char *s = "";
  // if (*width > len)
  s = apply_padding(*width, len, 0);
  return (s);
}

char *apply_precision(int *precision, char *affix, size_t len) {
  char *s = apply_padding(*precision, len, 1);
  char *output = ft_strjoin(s, affix);
  return (output);
}

void format_d(int d, t_format *format) {
  char *s = ft_itoa(d);

  char *width = apply_width(&format->width, ft_strlen(s));
  char *precision = apply_precision(&format->precision, s, ft_strlen(s));

  // if (width && precision) {
  char *output = ft_strjoin(width, precision);
  ft_putstr(output);
  // } else {
  //   ft_putstr(s);
  // }
}

void apply_format(t_format *format, va_list ap) {
  if (format->specifier == 'c') {
    char c = va_arg(ap, int);
  } else if (format->specifier == 's') {
    char *s = va_arg(ap, char *);
  } else if (format->specifier == 'p') {
    char *p = va_arg(ap, void *);
  } else if (format->specifier == 'd' || format->specifier == 'i') {
    format_d(va_arg(ap, int), format);
  } else if (format->specifier == 'u') {
    unsigned int u = va_arg(ap, unsigned int);
  } else if (format->specifier == 'x' || format->specifier == 'X') {
    char *x = va_arg(ap, char *);
  } else if (format->specifier == '%') {
    write(1, "%", 1);
  }
}

int parse_format(const char *conv_spec, va_list ap) {
  int count = 1;
  int offset = 0;
  t_format *format = create_struct();
  if (!format)
    return (0);

  while (*conv_spec) {
    if (ft_strchr("-+ 0#", *conv_spec))
      set_flags(format, conv_spec);
    else if (ft_strchr("0123456789", *conv_spec)) {
      offset = str_to_int(&format->width, conv_spec);
      conv_spec += offset;
      count += offset;
      continue;
    } else if (*conv_spec == '.') {
      conv_spec++;
      count++;
      offset = str_to_int(&format->precision, conv_spec);
      conv_spec += offset;
      count += offset;
      continue;
    } else if (ft_strchr("cspdiuxX%", *conv_spec)) {
      format->specifier = *conv_spec;
      // printf("[%d]", format->width);
      // printf("[%d]", format->precision);
      apply_format(format, ap);
      // printf("left_justify: %d \n", format->left_justify);
      // printf("force_sign: %d \n", format->force_sign);
      // printf("sign_space: %d \n", format->sign_space);
      // printf("zero_padd: %d \n", format->zero_padding);
      // printf("alter_form: %d \n", format->alternate_form);

      // ft_putnbr(va_arg(ap, int));
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

  ft_printf("maty a [%+10.5d] ans et son père [%1.5d] ans. \n", 24, 63);
  // printf("[%+4.5d] [%-10.5s] [%#010x] [% d] [%+d]\n", 42, "hello world",
  // 255,
  //  42, -42);
  // printf("[%d] [%s] [%x] [%d] [%d]\n", 42, "hello world", 255, 42,
  // -42);
}
