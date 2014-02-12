#include    "pic.h"

inline void outb(unsigned short port, unsigned char val) {
  __asm__ volatile ("\
      .intel_syntax\n\t\
      outb %0, %1\n\t\
      .att_syntax"
      :
      : "Nd" (port), "a" (val)
      );
}

inline unsigned char inb(unsigned short port) {
  unsigned char ret;
  __asm__ volatile ("\
      .intel_syntax\n\t\
      inb %0, %1\n\t\
      .att_syntax"
      : "=a" (ret) // output
      : "Nd" (port) // input
      );
  return (ret);
}

inline void io_wait(void) {
  __asm__ volatile ("\
      jmp io\n\t\
      io: jmp io2\n\t\
      io2:\n\
      ");
}

void PIC_remap(unsigned int offset1, unsigned int offset2)
{
  unsigned char a1, a2;

  a1 = inb(PIC1_DATA);                        // save masks
  a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
  io_wait();
  outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
  io_wait();
  outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2(0000 0100)
  io_wait();
  outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
  io_wait();

  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  outb(PIC1_DATA, a1);   // restore saved masks.
  io_wait();
  outb(PIC2_DATA, a2);
  io_wait();
}
