[BITS 32]

EXTERN putchar
GLOBAL _start

_start:
    xor eax, eax
    push eax
    mov al, 'k'
    call putchar
    pop eax

end:
    jmp end
