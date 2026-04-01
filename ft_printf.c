#include "ft_printf.h"

char *apply_width(t_format *format, char *input, size_t input_len) {
  size_t width = format->width;

  if (width > input_len) {
    char *output = malloc(width + 1);
    ft_memset(output,
              format->zero_padding && !format->force_sign &&
                      !format->alternate_form && !format->is_neg &&
                      !format->justify_left
                  ? '0'
                  : ' ',
              width - input_len);
    output = format->justify_left ? ft_strjoin(input, output)
                                  : ft_strjoin(output, input);
    output[width] = '\0';
    return (output);
  }
  return (input);
}

char *apply_precision(t_format *format, char *input, size_t input_len) {
  char spec = format->specifier;
  size_t precision = format->precision;

  if (spec == 'd' || spec == 'i' || spec == 'x' || spec == 'X' || spec == 'u') {
    if (precision > input_len) {
      char *output = malloc(precision + 1);
      ft_memset(output, '0', precision - input_len);
      output = ft_strjoin(output, input);
      output[precision] = '\0';
      return (output);
    }
  } else if (spec == 's') {
    if (precision < input_len) {
      char *output = malloc(precision + 1);
      ft_memcpy(output, input, precision);
      output[precision] = '\0';
      return (output);
    }
  }
  return (input);
}

char *apply_force_sign(int d, char *s, t_format *format) {
  if (format->sign_space && !format->force_sign) {
    return (ft_strjoin(" ", s));
  } else if (format->force_sign)
    return (ft_strjoin(d > 0 ? "+" : "-", s));
  return (s);
}

char *format_d(int d, t_format *format) {
  if (d < 0) {
    format->is_neg = 1;
    d = d * (-1);
  }
  char *s = ft_itoa(d);
  size_t input_len = ft_strlen(s);

  if (format->has_precision) {
    s = apply_precision(format, s, input_len);
    if (format->is_neg)
      s = ft_strjoin("-", s);
  }
  if (format->force_sign || format->sign_space)
    s = apply_force_sign(d, s, format);
  if (format->width)
    s = apply_width(format, s, ft_strlen(s));

  return (s);
}

char *format_s(char *s, t_format *format) {
  if (format->has_precision)
    s = apply_precision(format, s, ft_strlen(s));
  if (format->width)
    s = apply_width(format, s, ft_strlen(s));
  return (s);
}

char *format_c(int c, t_format *format) {
  char *s = char_to_str(c);
  if (format->width)
    s = apply_width(format, s, 1);
  return (s);
}

char *format_x(unsigned int x, t_format *format) {
  char *hex = ft_to_hex(x);

  if (format->has_precision)
    hex = apply_precision(format, hex, ft_strlen(hex));
  if (format->alternate_form)
    hex = ft_strjoin("0x", hex);
  if (format->width)
    hex = apply_width(format, hex, ft_strlen(hex));
  if (format->specifier == 'X')
    to_upper(hex);

  return (hex);
}

int u_len(unsigned int u) {
  int len = 0;
  unsigned int tmp = u;
  if (tmp == 0)
    len = 1;
  while (tmp != 0) {
    tmp /= 16;
    len++;
  }
  return (len);
}

char *u_to_str(unsigned int u) {
  int i = 0;
  char base10[] = "0123456789";

  char *s = malloc(u_len(u) + 1);

  while (u != 0) {
    s[i] = base10[u % 10];
    u /= 10;
    i++;
  }
  ft_rev_str(s);
  s[i] = '\0';

  return (s);
}

char *format_u(unsigned int u, t_format *format) {
  char *s = u_to_str(u);
  size_t input_len = ft_strlen(s);

  if (format->has_precision)
    s = apply_precision(format, s, input_len);
  if (format->width)
    s = apply_width(format, s, ft_strlen(s));

  return (s);
}

char *apply_format(t_format *format, va_list *ap) {
  if (format->specifier == 'c') {
    return (format_c(va_arg(*ap, int), format));
  } else if (format->specifier == 's') {
    return (format_s(va_arg(*ap, char *), format));
  } else if (format->specifier == 'p') {
    // char *p = va_arg(ap, void *);
  } else if (format->specifier == 'd' || format->specifier == 'i') {
    return (format_d(va_arg(*ap, int), format));
  } else if (format->specifier == 'u') {
    return (format_u(va_arg(*ap, unsigned int), format));
    // unsigned int u = va_arg(ap, unsigned int);
  } else if (format->specifier == 'x' || format->specifier == 'X') {
    return (format_x(va_arg(*ap, unsigned int), format));
  } else if (format->specifier == '%') {
    write(1, "%", 1);
  }
  return (NULL);
}

int parse_format(const char *conv_spec, va_list *ap) {
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
      format->has_precision = 1;
      offset = str_to_int(&format->precision, conv_spec);
      conv_spec += offset;
      count += offset;
      continue;
    } else if (ft_strchr("cspdiuxX%", *conv_spec)) {
      format->specifier = *conv_spec;

      // printf("left_justify: %d \n", format->justify_left);
      // printf("force_sign: %d \n", format->force_sign);
      // printf("sign_space: %d \n", format->sign_space);
      // printf("zero_padd: %d \n", format->zero_padding);
      // printf("alter_form: %d \n", format->alternate_form);
      // printf("width: %d \n", format->width);
      // printf("precision: %d \n", format->precision);
      // printf("specifier: %c \n", format->specifier);
      char *output = apply_format(format, ap);
      ft_putstr(output);

      return (count);
    }
    conv_spec++;
    count++;
  }

  return (count);
}

void print_str(const char *s, va_list *ap) {
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

void ft_printf(const char *s, ...) {
  va_list ap;

  va_start(ap, s);
  print_str(s, &ap);
  va_end(ap);
}

int main(void) {
  // char *str = "maty est 24 ans";
  ft_printf("maty a [%+.5d] ans et son père [%010.5d] ans. \n", 24000000, -63);
  printf("-------------------- \n");
  ft_printf("maty a [%+010.5d] ans et son père [%d] ans. \n", 24, 63);
  printf("-------------------- \n");
  ft_printf("[%-10.5s] \n", "hello world");
  printf("-------------------- \n");
  ft_printf("[%-10.5c] \n", 'c');
  printf("-------------------- \n");
  ft_printf("[%-#10.5X] [%#.3X] \n", 255, 355);
  printf("-------------------- \n");
  ft_printf("[%10.5i] [%-020u]  \n", -1, -1);
  printf("[%10.5i] [%-020u]  \n", -1, -1);
  printf("-------------------- \n");
  printf("-------------------- \n");
  printf(
      "[%+010.5d] [%-10.5s] [%-#10.5X] [%#.3X] [% d] [%10.5d] [%-10c] [%10.5i] "
      "[%u]\n",
      24, "hello world", 255, 355, 42, -42, 'c', -1, -1);
}
