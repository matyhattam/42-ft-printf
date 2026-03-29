#include "ft_printf.h"

char *apply_padding(t_format *format, char type, char *input, size_t input_len,
                    int is_precision) {
  int output_len = type == 'w' ? format->width : format->precision;
  int zpad = format->zero_padding;
  char *output = malloc(10000000);
  size_t pad_len;
  // if (output_len <= 0 || output_len <= input_len)
  if (output_len <= 0)
    return (NULL);

  if (output_len > input_len) {
    pad_len = output_len - input_len;
    // *output = malloc((pad_len + 1) * sizeof(char));
    if (format->specifier == 'd' || format->specifier == 'i') {
      ft_memset(output,
                is_precision || (!format->has_precision && zpad) ? '0' : ' ',
                pad_len);
    }
  } else {
    pad_len = format->precision;
    printf("%d", format->precision);
    // printf("%d", pad_len);
    // output = malloc((pad_len + 1) * sizeof(char));
    ft_strlcpy(output, input, pad_len);
  }

  // if (format->specifier == 's') {
  //   ft_strlcpy(output, input, pad_len);
  // }

  output[pad_len] = '\0';

  return (output);
}

char *apply_width(t_format *format, char *input, size_t input_len) {
  char spec = format->specifier;
  int width = format->width;

  if (width > input_len) {
    char *output = malloc(width + 1);
    ft_memset(output, format->zero_padding && !format->force_sign ? '0' : ' ',
              width - input_len);
    output = ft_strjoin(output, input);
    output[width] = '\0';
    return (output);
  }
  return (input);
}

char *apply_precision(t_format *format, char *input, size_t input_len) {
  char spec = format->specifier;
  int precision = format->precision;

  if (spec == 'd' || spec == 'i') {
    if (precision > input_len) {
      char *output = malloc(precision + 1);
      ft_memset(output, '0', precision - input_len);
      output = ft_strjoin(output, input);
      output[precision] = '\0';
      return (output);
    }
  }
  return (input);
}

char *apply_force_sign(int d, char *s, t_format *format) {
  if (format->sign_space && !format->force_sign) {
    return ft_strjoin(" ", s);
  } else if (format->force_sign)
    return ft_strjoin(d > 0 ? "+" : "-", s);
  return (s);
}

char *format_d(int d, t_format *format) {
  char *s = ft_itoa(d);
  size_t input_len = ft_strlen(s);

  if (format->has_precision)
    s = apply_precision(format, s, input_len);
  if (format->force_sign || format->sign_space)
    s = apply_force_sign(d, s, format);
  if (format->width)
    s = apply_width(format, s, ft_strlen(s));

  return (s);
}

char *format_s(char *s, t_format *format) {
  char *out;

  // printf("%d", format->specifier);
  // printf("%zu", ft_strlen(s));
  // if (format->has_precision)
  // out = apply_precision(format, s, ft_strlen(s));
  // if (format->width)
  //   out = ft_strjoin(apply_width(format, s, ft_strlen(s)), s);

  return (out);
  // return (s);
}

char *apply_format(t_format *format, va_list ap) {
  if (format->specifier == 'c') {
    char c = va_arg(ap, int);
  } else if (format->specifier == 's') {
    return (format_s(va_arg(ap, char *), format));
  } else if (format->specifier == 'p') {
    char *p = va_arg(ap, void *);
  } else if (format->specifier == 'd' || format->specifier == 'i') {
    return (format_d(va_arg(ap, int), format));
  } else if (format->specifier == 'u') {
    unsigned int u = va_arg(ap, unsigned int);
  } else if (format->specifier == 'x' || format->specifier == 'X') {
    char *x = va_arg(ap, char *);
  } else if (format->specifier == '%') {
    write(1, "%", 1);
  }
  return (NULL);
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
      format->has_precision = 1;
      offset = str_to_int(&format->precision, conv_spec);
      conv_spec += offset;
      count += offset;
      continue;
    } else if (ft_strchr("cspdiuxX%", *conv_spec)) {
      format->specifier = *conv_spec;

      // printf("left_justify: %d \n", format->left_justify);
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

  ft_printf("maty a [%+.5d] ans et son père [%d] ans. \n", 24000000, 63);
  printf("-------------------- \n");
  ft_printf("maty a [%+010.5d] ans et son père [%d] ans. \n", 24, 63);
  printf("-------------------- \n");
  // ft_printf("[%10.5s] \n", "hello world");
  printf("-------------------- \n");
  printf("[%+010.5d] [%-10.5s] [%#010x] [% d] [% d]\n", 24, "hello world", 255,
         42, -42);
  // printf("[%d] [%s] [%x] [%d] [%d]\n", 42, "hello world", 255, 42,
  // -42);
}
