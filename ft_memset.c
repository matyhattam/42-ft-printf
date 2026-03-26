#include "ft_printf.h"

void *ft_memset(void *s, int c, size_t n) {
  size_t i = 0;

  while (i < n) {
    ((char *)s)[i] = c;
    i++;
  }

  return (s);
}
