#include "ft_printf.h"

void ft_putnbr(int n) {
  long nl;

  nl = n;
  if (n < 0) {
    ft_putchar('-');
    nl = -nl;
  }
  if (nl > 100)
    ft_putnbr(nl / 10);
  else if ((nl / 10) > 0)
    ft_putchar((nl / 10) + '0');
  ft_putchar((nl % 10) + '0');
}
