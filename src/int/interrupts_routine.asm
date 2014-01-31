extern isr_default
extern isr_clock
extern isr_kb
global _asm_irq_default
global _asm_irq_0
global _asm_irq_1

_asm_irq_default:
    call isr_default
    mov al, 0x20
    out 0x20, al
    iret

_asm_irq_0:
    call isr_clock
    mov al, 0x20
    out 0x20, al
    iret

_asm_irq_1:
    call isr_kb
    mov al, 0x20
    out 0x20, al
    iret
