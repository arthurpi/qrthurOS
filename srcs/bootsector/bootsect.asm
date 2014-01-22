%define BASE    0x100
%define KSIZE   50

[BITS 16]
[ORG 0x0]

jmp start
%include    "srcs/bootsector/UTIL.INC"
start:
    ; Init at 0x07c0
    mov ax, 0x07c0
    mov ds, ax
    mov es, ax
    ; Init stack
    mov ax, 0x8000
    mov ss, ax ; Stack Segment
    mov sp, 0x9000 ; Stack pointer

    ; Retrieve boot unit
    mov [bootdrv], dl

    ; Display msg BIOS
    mov si, msg
    call afficher

    ; Load kernel
    xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0

    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es

    ; Init Global Description Table (GDT)
      ; Compute GDT limit
    mov ax, gdtend
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax

      ; Compute GDT linear address
    xor eax, eax
    mov ax, ds
    shl eax, 4
    xor ebx, ebx
    mov bx, gdt
    add eax, ebx
    mov dword [gdtptr + 2], eax

    ; Shutdown interrupts & Load GDT
    cli
    lgdt [gdtptr]

    ; Enable Protected Mode
    mov eax, cr0
    or ax, 1
    mov cr0, eax

    jmp next

next:
    
    ; Reinit Data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Reinit Stack segment
    mov ss, ax
    mov esp, 0x9F000

    ; Jump to kernel
    jmp dword 0x8:0x1000

; Variables
msg: db "Loading kernel...", 13, 10, 0
bootdrv: db 0

gdt:
  db 0, 0, 0, 0, 0, 0, 0, 0
gdt_cs:
  db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_ds:
  db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdtend:

gdtptr:
  dw 0
  dd 0

times 510-($-$$) db 144
dw 0xAA55
