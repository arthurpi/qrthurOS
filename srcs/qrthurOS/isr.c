#include    "screen.h"
#include    "isr.h"

void        isr_default(void)
{
  kputstring("default_interrupt\n");
}

void        isr_clock(void)
{
  kputstring("clock_interrupt\n");
}

void        isr_kb(void)
{
  kputstring("kb_interrupt\n");
}
