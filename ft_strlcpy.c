#include "ft_printf.h"

size_t ft_strlcpy(char *dest, const char *src, size_t size) {
  size_t i = 0;

  if (size == 0)
    return (ft_strlen(src));

  while (i < size - 1 && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  dest[i] = '\0';
  return (ft_strlen(src));
}
