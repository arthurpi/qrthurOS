#ifndef INCLUDES_IDT_H
# define INCLUDES_IDT_H

# define IDTBASE 0x7F8 // At the end of the GDT
# define IDTSIZE 0xFF
# define INTGATE 0x8E

struct idt {
  u16 lim0_15;
  u16 selector;
  u8 unused;
  u8 flags;
  u16 lim16_31;
} __attribute__((packed));

struct idtr {
  u16 lim;
  u32 base;
} __attribute__((packed));

typedef struct idt idt_t;
typedef struct idtr idtr_t;

idt_t idt[IDTSIZE];
idtr_t idtr;

#endif /* INCLUDES_IDT_H */
