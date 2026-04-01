#include "ft_printf.h"

char *apply_width(t_format *format, char *input, size_t input_len) {
  size_t width = format->width;

  if (width <= input_len)
    return (ft_strdup(input));

  char *buffer = malloc(width - input_len + 1);
  if (!buffer)
    return (NULL);

  ft_memset(buffer,
            format->zero_padding && !format->force_sign &&
                    !format->alternate_form && !format->is_neg &&
                    !format->justify_left
                ? '0'
                : ' ',
            width - input_len);
  buffer[width - input_len] = '\0';

  char *output = format->justify_left ? ft_strjoin(input, buffer)
                                      : ft_strjoin(buffer, input);

  free(buffer);
  return (output);
}

char *apply_precision(t_format *format, char *input, size_t input_len) {
  char spec = format->specifier;
  size_t precision = format->precision;

  if (spec == 'd' || spec == 'i' || spec == 'x' || spec == 'X' || spec == 'u') {
    if (precision > input_len) {
      char *buffer = malloc(precision - input_len + 1);
      if (!buffer)
        return (NULL);

      ft_memset(buffer, '0', precision - input_len);
      buffer[precision - input_len] = '\0';

      char *output = ft_strjoin(buffer, input);
      free(buffer);
      return (output);
    }
  } else if (spec == 's' || spec == 'p') {
    if (precision < input_len) {
      char *output = malloc(precision + 1);
      ft_memcpy(output, input, precision);
      output[precision] = '\0';
      return (output);
    }
  }
  return (ft_strdup(input));
}

static int replace(char **src, char *new) {
  if (!new)
    return (0);
  free(*src);
  *src = new;
  return (1);
}

char *apply_force_sign(char *s, t_format *format) {
  char *out;

  if (!s)
    return (NULL);

  if (format->sign_space && !format->force_sign)
    out = ft_strjoin(" ", s);
  else if (format->force_sign)
    out = ft_strjoin("+", s);
  else
    return (ft_strdup(s));

  return (out);
}

char *format_d(int d, t_format *format) {
  if (d < 0) {
    format->is_neg = 1;
    d = -d;
  }
  char *s = ft_itoa(d);
  if (!s)
    return (NULL);

  if (format->has_precision) {
    if (!replace(&s, apply_precision(format, s, ft_strlen(s))))
      return (NULL);
    if (format->is_neg)
      if (!replace(&s, ft_strjoin("-", s)))
        return (NULL);
  }
  if (format->force_sign || format->sign_space)
    if (!replace(&s, apply_force_sign(s, format)))
      return (NULL);
  if (format->width)
    if (!replace(&s, apply_width(format, s, ft_strlen(s))))
      return (NULL);

  return (s);
}

char *format_s(char *s, t_format *format) {
  char *buffer;
  if (!s)
    return (ft_strdup("(null)"));

  buffer = ft_strdup(s);
  if (!buffer)
    return (NULL);

  if (format->has_precision)
    if (!replace(&buffer, apply_precision(format, buffer, ft_strlen(buffer))))
      return (NULL);
  if (format->width)
    if (!replace(&buffer, apply_width(format, buffer, ft_strlen(buffer))))
      return (NULL);
  return (buffer);
}

char *format_c(int c, t_format *format) {
  if (c == '0') {
    char *s = malloc(1);
    if (!s)
      return (NULL);
    s[0] = '\0';
    return (s);
  }

  char *s = char_to_str(c);
  if (!s)
    return (NULL);

  if (format->width)
    if (!replace(&s, apply_width(format, s, 1)))
      return (NULL);
  return (s);
}

char *format_x(va_list *ap, t_format *format, int is_p) {
  unsigned long x;

  if (is_p) {
    x = (unsigned long)va_arg(*ap, void *);
  } else {
    x = (unsigned long)va_arg(*ap, unsigned int);
  }

  char *hex = ft_to_hex(x);
  if (!hex)
    return (NULL);

  if (format->has_precision && !is_p)
    if (!replace(&hex, apply_precision(format, hex, ft_strlen(hex))))
      return (NULL);
  if (format->alternate_form || is_p)
    if (!replace(&hex, ft_strjoin("0x", hex)))
      return (NULL);
  if (format->width)
    if (!replace(&hex, apply_width(format, hex, ft_strlen(hex))))
      return (NULL);
  if (format->specifier == 'X')
    to_upper(hex);

  return (hex);
}

char *format_u(unsigned int u, t_format *format) {
  char *s = u_to_str(u);
  if (!s)
    return (NULL);

  if (format->has_precision)
    if (!replace(&s, apply_precision(format, s, ft_strlen(s))))
      return (NULL);
  if (format->width)
    if (!replace(&s, apply_width(format, s, ft_strlen(s))))
      return (NULL);

  return (s);
}

char *apply_format(t_format *format, va_list *ap) {
  if (format->specifier == 'c') {
    return (format_c(va_arg(*ap, int), format));
  } else if (format->specifier == 's') {
    return (format_s(va_arg(*ap, char *), format));
  } else if (format->specifier == 'p') {
    return (format_x(ap, format, 1));
  } else if (format->specifier == 'd' || format->specifier == 'i') {
    return (format_d(va_arg(*ap, int), format));
  } else if (format->specifier == 'u') {
    return (format_u(va_arg(*ap, unsigned int), format));
  } else if (format->specifier == 'x' || format->specifier == 'X') {
    return (format_x(ap, format, 0));
    // } else if (format->specifier == '%') {
    // write(1, "%", 1);
    // return (ft_strdup("%"));
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
    } else if (*conv_spec == '%') {
      // write(1, "%", 1);
      return (count);
    } else if (ft_strchr("cspdiuxX", *conv_spec)) {
      format->specifier = *conv_spec;
      char *output = apply_format(format, ap);

      if (output) {
        ft_putstr(output);
        free(output);
      }

      free(format);
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

// int main(void) {
//   ft_printf("maty a [%+.5d] ans et son père [%08.5d] ans. \n", 24000, -63);
//   printf("maty a [%+.5d] ans et son père [%08.5d] ans. \n", 24000, -63);
//   printf("-------------------- \n");
//   ft_printf("[%-.5s] [%-10.5s] \n", "hello world", "maty hattam");
//   printf("[%-.5s] [%-10.5s] \n", "hello world", "maty hattam");
//   printf("-------------------- \n");
//   ft_printf("[%-10c] \n", 'c');
//   printf("[%-10c] \n", 'c');
//   printf("-------------------- \n");
//   ft_printf("[%-#10.5X] [%#.3X] \n", 255, 355);
//   printf("[%-#10.5X] [%#.3X] \n", 255, 355);
//   printf("-------------------- \n");
//   ft_printf("[%10.5i] [%-020u]  \n", -1, -16);
//   printf("[%10.5i] [%-20u]  \n", -1, -16);
//   printf("-------------------- \n");
//   int i = 10;
//   int *p = &i;
//   ft_printf("[%-20p] \n", &p);
//   printf("[%-20p] \n", &p);
//   printf("-------------------- \n");
// }

int main(void) {
  ft_printf("%c \n", '0');
  printf("%c \n", 0);
  printf("-------------------- \n");
  ft_printf("%%%%%% \n");
  printf("%%%%%% \n");
}
