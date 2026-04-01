#include "ft_printf.h"

char *ft_strdup(char *s) {
  char *dup = malloc(ft_strlen(s) + 1);
  int i = 0;

  while (s[i] != '\0') {
    dup[i] = s[i];
    i++;
  }

  dup[i] = '\0';
  return dup;
}
