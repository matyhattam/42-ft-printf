#include "ft_printf.h"

char *apply_width(t_format *fmt, char *input, size_t input_len) {
  size_t width = fmt->width;
  if (width <= input_len)
    return (ft_strdup(input));

  char *buffer = malloc(width - input_len + 1);
  if (!buffer)
    return (NULL);

  int is_zpadded = fmt->z_padding && !fmt->f_sign && !fmt->alt_form &&
                   !fmt->justify && !fmt->has_precision;
  ft_memset(buffer, is_zpadded ? '0' : ' ', width - input_len);
  buffer[width - input_len] = '\0';

  if (fmt->is_neg && fmt->z_padding && !fmt->has_precision) {
    buffer[0] = '-';
    input[0] = '0';
  }

  char *output =
      fmt->justify ? ft_strjoin(input, buffer) : ft_strjoin(buffer, input);

  free(buffer);
  return (output);
}

char *apply_width_c(t_format *fmt, char *c) {
  size_t width = fmt->width < 1 ? 1 : fmt->width;
  char *buf = malloc(width + 1);
  if (!buf)
    return (NULL);

  ft_memset(buf, ' ', width);
  buf[width] = '\0';

  if (fmt->justify)
    buf[0] = c[0];
  else
    buf[width - 1] = c[0];

  return (buf);
}

char *apply_precision(t_format *fmt, char *input, size_t input_len) {
  char spec = fmt->specifier;
  size_t precision = fmt->precision;

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
    if (precision < input_len && ft_strcmp(input, "(null)") != 0) {
      char *output = malloc(precision + 1);
      if (!output)
        return (NULL);

      ft_memcpy(output, input, precision);
      output[precision] = '\0';

      return (output);
    } else if (precision < input_len && ft_strcmp(input, "(null)") == 0) {
      return (NULL);
    }
  }
  return (ft_strdup(input));
}

char *apply_force_sign(char *s, t_format *fmt) {
  char *out;

  if (!s)
    return (NULL);

  if (fmt->s_space && !fmt->f_sign && !fmt->is_neg)
    out = ft_strjoin(" ", s);
  else if (fmt->f_sign && !fmt->is_neg)
    out = ft_strjoin("+", s);
  else
    return (ft_strdup(s));

  return (out);
}

char *format_d(int d, t_format *fmt) {
  if (d < 0) {
    fmt->is_neg = 1;
    d = -d;
  }
  char *s = ft_itoa(d);
  if (!s)
    return (NULL);

  if (fmt->has_precision && fmt->precision == 0 && d == 0)
    if (!replace(&s, ft_strdup(""))) {
      free(s);
      return (NULL);
    }
  if (fmt->has_precision)
    if (!replace(&s, apply_precision(fmt, s, ft_strlen(s))))
      return (NULL);
  if (fmt->is_neg)
    if (!replace(&s, ft_strjoin("-", s)))
      return (NULL);
  if (fmt->f_sign || fmt->s_space)
    if (!replace(&s, apply_force_sign(s, fmt)))
      return (NULL);
  if (fmt->width)
    if (!replace(&s, apply_width(fmt, s, ft_strlen(s))))
      return (NULL);

  return (s);
}

char *format_s(char *s, t_format *fmt) {
  char *buffer;
  if (!s) {
    buffer = ft_strdup("(null)");
  } else {
    buffer = ft_strdup(s);
  }
  if (!buffer)
    return (NULL);

  if (fmt->has_precision)
    if (!replace(&buffer, apply_precision(fmt, buffer, ft_strlen(buffer)))) {
      free(buffer);
      return (NULL);
    }
  if (fmt->width)
    if (!replace(&buffer, apply_width(fmt, buffer, ft_strlen(buffer)))) {
      free(buffer);
      return (NULL);
    }
  return (buffer);
}

char *format_c(int c, t_format *fmt) {
  char *s;
  if (c == '\0') {
    s = malloc(1);
    if (!s)
      return (NULL);
    s[0] = '\0';
  } else {
    s = char_to_str(c);
  }

  if (!s)
    return (NULL);

  if (fmt->width)
    if (!replace(&s, apply_width_c(fmt, s)))
      return (NULL);
  return (s);
}

char *format_x(va_list *ap, t_format *fmt, int is_p) {
  unsigned long x;
  char *hex;

  if (is_p) {
    x = (unsigned long)va_arg(*ap, void *);
  } else {
    x = (unsigned long)va_arg(*ap, unsigned int);
  }
  if (x == 0 && is_p) {
    hex = ft_strdup("(nil)");
  } else {
    hex = ft_to_hex(x);
  }

  if (!hex)
    return (NULL);

  if (fmt->has_precision && fmt->precision == 0 && x == 0)
    if (!replace(&hex, ft_strdup(""))) {
      free(hex);
      return (NULL);
    }
  if (fmt->has_precision && !is_p)
    if (!replace(&hex, apply_precision(fmt, hex, ft_strlen(hex))))
      return (NULL);
  if ((fmt->alt_form && x != 0) || (x != 0 && is_p))
    if (!replace(&hex, ft_strjoin("0x", hex)))
      return (NULL);
  if (fmt->width)
    if (!replace(&hex, apply_width(fmt, hex, ft_strlen(hex))))
      return (NULL);
  if (fmt->specifier == 'X')
    to_upper(hex);

  return (hex);
}

char *format_u(unsigned int u, t_format *fmt) {
  char *s = u_to_str(u);
  if (!s)
    return (NULL);

  if (fmt->has_precision && fmt->precision == 0 && u == 0)
    if (!replace(&s, ft_strdup(""))) {
      free(s);
      return (NULL);
    }

  if (fmt->has_precision)
    if (!replace(&s, apply_precision(fmt, s, ft_strlen(s))))
      return (NULL);
  if (fmt->width)
    if (!replace(&s, apply_width(fmt, s, ft_strlen(s))))
      return (NULL);

  return (s);
}
