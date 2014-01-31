#include    "screen.h"
#include    "isr.h"

void        isr_default(void)
{
  kputstring("default_interrupt\n");
}

void        isr_clock(void)
{
  static unsigned int tick = 0;

  if (++tick > 99) {
    kputstring("clock_sec\n");
    tick = 0;
  }
}

void        isr_kb(void)
{
  /*
  uchar c = 0;

  do {
    c = inb(0x60);
  } while (c & 0x01 == 0); */
  kputstring("kb_interrupt\n");
}
