#include "ft_printf.h"

void *ft_calloc(size_t nmemb, size_t size) {
  if (size && nmemb > SIZE_MAX / size)
    return NULL;

  size_t total = nmemb * size;
  char *arr = malloc(total ? total : 1);
  if (!arr)
    return NULL;

  ft_memset(arr, 0, total);

  return (arr);
}
