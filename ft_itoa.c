#include "ft_printf.h"

int num_size(int n) {
  int i = 0;

  if (n == 0)
    return (1);

  while (n != 0) {
    n /= 10;
    i++;
  }
  return (i);
}

void ft_rev_str(char *s) {
  size_t s_len = ft_strlen(s);
  size_t i = 0;
  size_t j = s_len - 1;
  char tmp;
  while (i < s_len / 2) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    i++;
    j--;
  }
}

char *ft_itoa(int n) {
  size_t len = num_size(n);
  char *nstr = malloc(len + 1);
  if (!nstr)
    return (NULL);

  if (n == 0) {
    nstr[0] = '0';
    nstr[1] = '\0';
    return (nstr);
  }

  long ui = (long)n;
  if (n < 0)
    ui *= -1;

  size_t i = 0;
  while (ui != 0) {
    nstr[i] = (ui % 10) + '0';
    ui /= 10;
    i++;
  }

  nstr[i] = '\0';
  ft_rev_str(nstr);

  return (nstr);
}
