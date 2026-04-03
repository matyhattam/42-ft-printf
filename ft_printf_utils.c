#include "ft_printf.h"

t_format *create_struct() { return (ft_calloc(1, sizeof(t_format))); }

char *char_to_str(int c) {
  char *s = malloc(2);
  if (!s)
    return NULL;

  s[0] = (char)c;
  s[1] = '\0';
  return s;
}

int ulen(unsigned int u) {
  int len = 0;
  unsigned int tmp = u;
  if (tmp == 0)
    len = 1;
  while (tmp != 0) {
    tmp /= 10;
    len++;
  }
  return (len);
}

char *u_to_str(unsigned int u) {
  int i = 0;
  char base10[] = "0123456789";

  char *s = malloc(ulen(u) + 1);
  if (!s)
    return (NULL);

  if (u == 0) {
    s[0] = '0';
    s[1] = '\0';
    return (s);
  }

  while (u != 0) {
    s[i] = base10[u % 10];
    u /= 10;
    i++;
  }

  s[i] = '\0';
  ft_rev_str(s);

  return (s);
}

int replace(char **src, char *new) {
  if (!new)
    return (0);
  free(*src);
  *src = new;
  return (1);
}
