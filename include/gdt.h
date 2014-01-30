#ifndef INCLUDES_GDT_H_
# define INCLUDES_GDT_H_

# include   "types.h"

# define GDTBASE 0x0
# define GDTSIZE 0xFF

struct dt {
  u16 lim0_15;
  u16 base0_15;
  u8 base16_23;
  u8 access;
  u8 lim19_16 : 4;
  u8 flags : 4;
  u8 base24_31;
} __attribute__ ((packed));

struct gdtr {
  u16 lim; // Size
  u32 base; // Starting addr
} __attribute__ ((packed));

typedef struct dt kdt_t;
typedef struct gdtr kgdtr_t;

kdt_t kgdt[GDTSIZE];
kgdtr_t kgdtr;

void        init_gdt(void);
void        init_dt(u32, u32, u8, u8, kdt_t *);

#endif /* INCLUDES_GDT_H_ */
