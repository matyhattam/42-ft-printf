#include "ft_printf.h"

void parse_str(const char *s, va_list ap) {
  // ft_putstr(va_arg(ap, char *));
  size_t i = 0;
  while (s[i] != '\0') {
    ft_putchar(s[i]);
    if (s[i] == '%') {
      ft_putnbr(va_arg(ap, int));
    }
    i++;
  }
}

int ft_printf(const char *s, ...) {
  va_list ap;
  int count;

  va_start(ap, s);
  parse_str(s, ap);
  va_end(ap);

  return (count);
}

int main(void) {
  // char *str = "maty est 24 ans";

  ft_printf("maty a %d ans et son père %d ans", 24, 63);
}
