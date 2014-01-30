#include    "memcpy.h"

void        *memcpy(char *dst, char *src, int n)
{
  void      *r = dst;

  while (n--)
    *(dst)++ = *(src)++;
  return (r);
}
