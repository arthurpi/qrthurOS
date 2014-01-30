#include    "gdt.h"
#include    "screen.h"

int         main(void);

void        _start(void)
{
  kY = 18;
  init_idt();
  init_pic();
  kputstring("Loading new GDT\n");
  PIC_remap(0x20, 0x70);
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
  //__asm__ ("sti"::);
  while (1);
}
