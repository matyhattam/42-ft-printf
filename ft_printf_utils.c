#include "ft_printf.h"

t_format *create_struct() { return (ft_calloc(1, sizeof(t_format))); }

void set_flags(t_format *format, const char *conv_spec) {
  if (*conv_spec == '-')
    format->justify_left = 1;
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

// char *apply_padding(t_format *format, char type, size_t input_len,
//                     int is_precision) {
//   int output_len = type == 'w' ? format->width : format->precision;
//   int zpad = format->zero_padding;

//   if (output_len <= 0 || output_len <= input_len)
//     return (NULL);

//   size_t pad_len = output_len - input_len;
//   char *output = malloc((pad_len + 1) * sizeof(char));
//   if (format->specifier == 'd' || format->specifier == 'i') {
//     ft_memset(output,
//               is_precision || (!format->has_precision && zpad) ? '0' : ' ',
//               pad_len);
//   }
//   output[pad_len] = '\0';

//   printf("%s ", output);
//   return (output);
// }
