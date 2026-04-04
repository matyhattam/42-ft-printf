#include "ft_printf.h"

char *ft_strchr(const char *s, int c) {
  size_t i = 0;

  while (s[i]) {
    if (s[i] == c) {
      return ((char *)&s[i]);
    }
    i++;
  }

  if (s[i] == (char)c)
    return ((char *)&s[i]);

  return (NULL);
}
