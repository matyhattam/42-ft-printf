#include "ft_printf.h"

int hex_len(unsigned int x) {
  int len = 0;
  unsigned int tmp = x;
  if (tmp == 0)
    len = 1;
  while (tmp != 0) {
    tmp /= 16;
    len++;
  }
  return (len);
}

char *ft_to_hex(unsigned int x) {
  int i = 0;
  char hex_digits[] = "0123456789abcdef";

  char *hex = malloc(hex_len(x) + 1);

  while (x != 0) {
    hex[i] = hex_digits[x % 16];
    x /= 16;
    i++;
  }
  ft_rev_str(hex);
  hex[i] = '\0';

  return (hex);
}