# define SCREENBASE 0xB8000
# define SCREENSIZE 0xFA0
# define SCREENLIM 0xB8FA0

char kX = 0;
char kY = 0;
char kAttr = 0x57;

void        kputchar(unsigned char c)
{
  unsigned char *slot;

  if (c == 10) {
    kX = 0;
    kY++;
  } else if (c == 9)
    kX += 8 - (kX % 8);
  else {
    slot = (unsigned char *) (SCREENBASE + (kX * 2) + (kY * 160));
    *slot = c;
    *(slot + 1) = kAttr;
  }
  if (++kX > 79) {
    kX = 0;
    kY++;
  }
  if (kY > 24) {
    kY = 0;
  }
}
