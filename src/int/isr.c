#include    "screen.h"
#include    "isr.h"
#include    "kbmap.h"


void        isr_default(void)
{
  kputstring("default_interrupt\n");
}

void        isr_clock(void)
{
  return ;
  /*
  static unsigned int tick = 0;

  if (++tick > 99) {
    kputstring("clock_sec\n");
    tick = 0;
  }
  */
}

void        isr_kb(void)
{
  static unsigned char current_key = 0;
  static unsigned char left_shift = 0;
  static unsigned char right_shift = 0;
  static unsigned char left_alt = 0;
  unsigned char scan_code = 0;
  unsigned char state = PUSH;

  do {
    scan_code = inb(0x64);
  } while (scan_code & 0x01 == 0x0);
  scan_code = 0;
  scan_code = inb(0x60);
  if (scan_code > 0x80) {
    state = REL;
    scan_code -= 0x80;
  }
  if (scan_code == LSHIFT)
    left_shift = state == PUSH ? 1 : 0;
  else if (scan_code == RSHIFT) {
    right_shift = state == PUSH ? 1 : 0;
  }
  else if (scan_code == LALT)
    left_alt = state == PUSH ? 1 : 0;
  else if (state == PUSH) // press
    kputchar(kbmap[(scan_code * 2) + (left_shift | right_shift)]);
}
