#include "ft_printf.h"

t_format *create_struct() { return (ft_calloc(1, sizeof(t_format))); }

int replace(char **src, char *new) {
  if (!new)
    return (0);
  free(*src);
  *src = new;
  return (1);
}

char *ft_ctostr(int c) {
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

char *ft_utostr(unsigned int u) {
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

int xlen(unsigned long x) {
  int len = 0;
  unsigned long tmp = x;
  if (tmp == 0)
    len = 1;
  while (tmp != 0) {
    tmp /= 16;
    len++;
  }
  return (len);
}

char *ft_tohex(unsigned long x) {
  int i = 0;
  char hex_digits[] = "0123456789abcdef";

  char *hex = malloc(xlen(x) + 1);
  if (!hex)
    return (NULL);

  if (x == 0) {
    hex[0] = '0';
    hex[1] = '\0';
    return (hex);
  }

  while (x != 0) {
    hex[i] = hex_digits[x % 16];
    x /= 16;
    i++;
  }

  hex[i] = '\0';
  ft_rev_str(hex);

  return (hex);
}

void to_upper(char *hex) {
  int i = 0;
  while (hex[i] != '\0') {
    if ((hex[i] >= 'a' && hex[i] <= 'f') || hex[i] == 'x')
      hex[i] -= 32;
    i++;
  }
}
