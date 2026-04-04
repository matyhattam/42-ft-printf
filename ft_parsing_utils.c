#include "ft_printf.h"

char *parse_specs(t_format *fmt, va_list *ap) {
  if (fmt->specifier == 'c') {
    return (format_c(va_arg(*ap, int), fmt));
  } else if (fmt->specifier == 's') {
    return (format_s(va_arg(*ap, char *), fmt));
  } else if (fmt->specifier == 'p') {
    return (format_x(ap, fmt, 1));
  } else if (fmt->specifier == 'd' || fmt->specifier == 'i') {
    return (format_d(va_arg(*ap, int), fmt));
  } else if (fmt->specifier == 'u') {
    return (format_u(va_arg(*ap, unsigned int), fmt));
  } else if (fmt->specifier == 'x' || fmt->specifier == 'X') {
    return (format_x(ap, fmt, 0));
  }
  return (NULL);
}

int parse_fmt(const char *fmt_specs, va_list *ap) {
  int offset = 0;
  int len = 0;
  int bytes = 0;
  t_format *fmt = create_struct();
  if (!fmt)
    return (0);

  while (*fmt_specs) {
    if (ft_strchr("-+ 0#", *fmt_specs)) {
      set_flags(fmt, fmt_specs);
    } else if (ft_strchr("0123456789", *fmt_specs)) {
      offset = parse_w_p(&fmt->width, fmt_specs);
      fmt_specs += offset;
      continue;
    } else if (*fmt_specs == '.') {
      fmt_specs++;
      fmt->has_precision = 1;
      offset = parse_w_p(&fmt->precision, fmt_specs);
      fmt_specs += offset;
      continue;
    } else if (*fmt_specs == '%') {
      write(1, "%", 1);
      free(fmt);
      return (1);
    } else if (ft_strchr("cspdiuxX", *fmt_specs)) {
      fmt->specifier = *fmt_specs;
      char *output = parse_specs(fmt, ap);
      if (!output) {
        free(fmt);
        return (0);
      }
      if (fmt->specifier == 'c') {
        bytes = write(1, output, fmt->width ? fmt->width : 1);
        free(output);
        free(fmt);
        return (bytes);
      } else {
        len = ft_strlen(output);
        ft_putstr(output);
      }
      free(output);
      free(fmt);
      return (len);
    }
    fmt_specs++;
  }

  free(fmt);
  return (0);
}

void set_flags(t_format *format, const char *conv_spec) {
  if (*conv_spec == '-')
    format->justify = 1;
  else if (*conv_spec == '+')
    format->f_sign = 1;
  else if (*conv_spec == ' ')
    format->s_space = 1;
  else if (*conv_spec == '0')
    format->z_padding = 1;
  else if (*conv_spec == '#')
    format->alt_form = 1;
}

int parse_w_p(int *fmt_field, const char *conv_spec) {
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
