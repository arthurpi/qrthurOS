#include    "gdt.h"
#include    "memcpy.h"
#include    "types.h"

void        init_dt(u32 base, u32 lim, u8 access, u8 other, kdt_t *dt)
{
  int i = 0;
  dt->lim0_15 = (lim & 0xFFFF); // 16 bits
  dt->base0_15 = (base & 0xFFFF); // 16 bits
  dt->base16_23 = (base & 0xFF0000) >> 16; // 8 bits
  dt->access = access; // 8 bits
  dt->lim19_16 = (lim & 0xF0000) >> 16; // 4 bits
  dt->flags = (other & 0xF); // 4 bits
  dt->base24_31 = (base & 0xFF000000) >> 24; // 8 bits
}

void        init_gdt(void)
{
  init_dt(0x0, 0x0, 0x0, 0x0, &kgdt[0]); // gdt
  init_dt(0x0, 0xFFFF, 0x9B, 0x0D, &kgdt[1]); // code
  init_dt(0x0, 0xFFFF, 0x93, 0x0D, &kgdt[2]); // data
  init_dt(0x0, 0x0, 0x97, 0x0D, &kgdt[3]); // stack

  kgdtr.base = GDTBASE;
  kgdtr.lim = GDTSIZE * 8;

  memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.lim);

  __asm__("\
      lgdtl (kgdtr)\n\t\
      movw $0x10, %ax\n\
      movw %ax, %ds\n\t\
      movw %ax, %es\n\t\
      movw %ax, %fs\n\t\
      movw %ax, %gs\n\t\
      ljmp $0x08, $next\n\t\
    next:\n\
      ");
}
