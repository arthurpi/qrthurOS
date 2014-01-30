#include    "types.h"

# define SCREENBASE 0xB8000
# define SCREENSIZE 0xFA0
# define SCREENLIM 0xB8FA0

unsigned char kX = 0;
unsigned char kY = 0;
unsigned char kAttr = 0x07;

void        kscroll(unsigned int n)
{
  unsigned int i = 0;
  unsigned int lim = SCREENSIZE - 160 * n;
  unsigned char *pos = (unsigned char *) SCREENBASE;

  for (; i < SCREENSIZE; i += 2) {
    if (i < lim) {
      *(pos + i) = *(pos + i + 160 * n);
      *(pos + i + 1) = *(pos + i + 1 + 160 * n);
    } else {
      *(pos + i) = 0;
      *(pos + i + 1) = 0;
    }
  }
  kY--;
}

void        kputchar(unsigned char c)
{
  if (c == 10) { // new line
    kY++;
    kX = 0;
  } else { // character
    unsigned char *pos = (unsigned char *) (SCREENBASE + kX * 2 + kY * 160);
    *pos = c;
    *(pos + 1) = kAttr;
    if (++kX > 79) {
      kX = 0;
      kY++;
    }
  }
  if (kY > 24) {
    kscroll(1);
  }
}

void        kputstring(unsigned char *s)
{
  for (; *s; s++) {
    kputchar(*s);
  }
}

void        kclearscreen(void)
{
  unsigned char *pos = (unsigned char *) SCREENBASE;
  unsigned int i = 0;

  for (; i < SCREENSIZE; i += 2) {
    *(pos + i) = ' ';
    *(pos + i + 1) = 0x0;
  }
}
