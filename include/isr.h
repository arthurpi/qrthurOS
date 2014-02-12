#ifndef INCLUDES_ISR_H
# define INCLUDES_ISR_H

# define PUSH 0
# define REL 1;

# define ESC 0x1B
# define BSPACE 0x0E
# define LCTRL 0x1D
# define LSHIFT 0x2A
# define RSHIFT 0x36
# define LALT 0x38
# define CAPSLOCK 0x3A

void        isr_default(void);
void        isr_clock(void);
void        isr_kb(void);

#endif /* INCLUDES_ISR_H */
