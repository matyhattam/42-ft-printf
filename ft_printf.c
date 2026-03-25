#include "ft_printf.h"

void parse_specifier(const char *specifier, va_list ap) {
  while (*specifier) {
    if (ft_strchr("-+ 0#", *specifier))
      break;
    else if (ft_strchr("cspdiuxX%", *specifier)) {
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

  ft_printf("maty a %d ans et son père %d ans", 24, 63);
  // printf("[%+10.5d] [%-10.5s] [%#010x] [% d] [%+d]\n", 42, "hello world",
  // 255,
  //  42, -42);
  // printf("[%d] [%s] [%x] [%d] [%d]\n", 42, "hello world", 255, 42,
  // -42);
}
