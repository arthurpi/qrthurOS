#include    "gdt.h"
#include    "screen.h"

int         main(void);

void        _start(void)
{
  kY = 18;
  kputstring("Loading new GDT\n");
  init_gdt();
  __asm__("\
      movw $0x18, %ax\n\
      movw %ax, %ss\n\
      movl $0x20000, %esp\n\
      ");
  main();
}

int         main(void)
{
  kputstring("New GDT loaded\n");
  kputstring("Loading IDT\n");
  init_idt();
  PIC_remap(0x20, 0x70);
  __asm__ ("sti");
  kputstring("Interrupts enabled\n");
  while (1);
}
