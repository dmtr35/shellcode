.section .text
.global func_shellcode


func_shellcode:
    xorq %rax, %rax
    pushq %rdx
    pushq %rcx
    xorq %rdx, %rdx
    xorq %rcx, %rcx
.iter:
    movw (%rdi, %rcx, 2), %ax
    cmpb $0, %al
    je .exit

    mov %ah, %dl
    shr $4, %dl
    cmp $0x06, %dl
    je .byte_al_letter
    cmp $0x03, %dl
    je .byte_al_num

.next_ah:
    mov %al, %dl
    shr $4, %dl
    cmp $0x06, %dl
    je .byte_ah_letter
    cmp $0x03, %dl
    je .byte_ah_num

.copy_ax:
    orb %ah, %al
    movb %al, (%rsi, %rcx)
    incq %rcx
    jmp .iter
   
.byte_al_letter:
    cmp $0x61, %ah
    jne .+6
    mov $0x0A, %ah
    jmp .next_ah
    cmp $0x62, %ah
    jne .+6
    mov $0x0B, %ah
    jmp .next_ah
    cmp $0x63, %ah
    jne .+6
    mov $0x0C, %ah
    jmp .next_ah
    cmp $0x64, %ah
    jne .+6
    mov $0x0D, %ah
    jmp .next_ah
    cmp $0x65, %ah
    jne .+6
    mov $0x0E, %ah
    jmp .next_ah
    cmp $0x66, %ah
    jne .+6
    mov $0x0F, %ah
    jmp .next_ah
.byte_al_num:
    shl $4, %ah
    shr $4, %ah
    jmp .next_ah

.byte_ah_letter:
    cmp $0x61, %al
    jne .+6
    mov $0xA0, %al
    jmp .copy_ax
    cmp $0x62, %al
    jne .+6
    mov $0xB0, %al
    jmp .copy_ax
    cmp $0x63, %al
    jne .+6
    mov $0xC0, %al
    jmp .copy_ax
    cmp $0x64, %al
    jne .+6
    mov $0xD0, %al
    jmp .copy_ax
    cmp $0x65, %al
    jne .+6
    mov $0xE0, %al
    jmp .copy_ax
    cmp $0x66, %al
    jne .+6
    mov $0xF0, %al
    jmp .copy_ax

.byte_ah_num:
    shl $4, %al
    jmp .copy_ax

.exit:
    movb $0, (%rsi, %rcx)
    popq %rcx
    popq %rdx
    ret
