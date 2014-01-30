%define BASE    0x100
%define KSIZE   50

[BITS 16]
[ORG 0x0]

jmp start
%include    "srcs/bootsector/UTIL.INC"
start:
    ; Init Data Segment at 0x07c0
    mov ax, 0x07c0
    mov ds, ax
    mov es, ax

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

    mov ah, 2 ; Read Sectors from Drive
    mov al, KSIZE ; Number of sector to read (512 bytes each)
    mov ch, 0 ; Cylinder 1
    mov cl, 2 ; Sector 2 (First sector contains this boot sector)
    mov dh, 0 ; Head
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
    mov cr0, eax ; Lowest bit of cr0 is now set to 1

    jmp next

next:

    ; Reinit Data segments
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
bootdrv: db 0
msg: db "Loading kernel...", 13, 10, 0

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
