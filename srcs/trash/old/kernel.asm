[BITS 32]
[ORG 0x1000]

    ; Display message using RAM video
    mov byte [0xB8000], 'F'
    mov byte [0xB8001], 0x57
    mov byte [0xB8002], 'D'
    mov byte [0xB8003], 0x57
    mov byte [0xB8004], 'P'
    mov byte [0xB8005], 0x57

end:
    jmp end

msg00: db "Kernel loaded...", 10, 0
