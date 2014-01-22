afficher:
    push ax
    push bx
.debut:
    lodsb       ; load a byte from ds:si to al
    cmp al, 0   ; check if string is over
    jz  .fin
    mov ah, 0x0e
    mov bx, 0x07
    int 0x10
    jmp .debut
.fin:
    pop bx
    pop ax
    ret
