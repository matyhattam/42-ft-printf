#include "ft_printf.h"

int print_str(const char *s, va_list *ap) {
  size_t i = 0;
  int total = 0;
  int slen = 0;

  while (s[i]) {
    if (s[i] == '%') {
      i++;
      slen += parse_fmt(&s[i], ap);
      while (!ft_strchr("cspdiuxX%", s[i]))
        i++;
      i++;
      continue;
    }
    ft_putchar(s[i]);
    total++;
    i++;
  }

  return (total + slen);
}

int ft_printf(const char *s, ...) {
  va_list ap;
  int count = 0;

  va_start(ap, s);
  count = print_str(s, &ap);
  va_end(ap);

  return (count);
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

// int main(void) {
//   ft_printf("%-2c%-3c%-4c*", 0, 'a', 0);
//   printf("------------------------ \n");
//   ft_printf("%-2c%-3c%-4c*", 0, 'a', 0);
// }
