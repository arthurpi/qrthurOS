#include    "types.h"
#include    "memcpy.h"
#include    "idt.h"

extern _asm_irq_default;
extern _asm_irq_0;
extern _asm_irq_1;

void        set_interrupt_descriptor(u32 lim, u16 selector, u16 flags, idt_t *idt)
{
  idt->lim0_15 = lim & 0xFFFF;
  idt->selector = selector;
  idt->unused = 0x0;
  idt->flags = flags;
  idt->lim16_31 = (lim & 0xFFFF0000) >> 0x10;
}

void        init_idt(void)
{
  int i = 0;

  for (; i < IDTSIZE; i++)
    set_interrupt_descriptor((u32) _asm_irq_default, 0x08, INTGATE, &idt[i]);
  set_interrupt_descriptor((u32) _asm_irq_0, 0x08, INTGATE, &idt[0x20]);
  set_interrupt_descriptor((u32) _asm_irq_1, 0x08, INTGATE, &idt[0x21]);

  idtr.lim = IDTSIZE * 8;
  idtr.base = IDTBASE;

  memcpy((char *) idtr.base, (char *) idt, idtr.lim);

  __asm__("lidtl (idtr)");
}
