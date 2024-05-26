section .text
global func_shellcode

%macro check_al_ah 3
    mov dl, %1
    shr dl, 4
    cmp dl, 00000110b
    je %2
    cmp dl, 00000011b
    je %3
%endmacro
%macro copy_byte 4
    cmp %1, %2
    jne short 5
    mov %1, %3
    jmp .%4
%endmacro

; <-- malloc [byte RSI] asm_func_shellcode(readonly [byte RDI], malloc [byte RSI]) -->
func_shellcode:
    xor rax, rax
    push rdx
    push rcx
    xor rdx, rdx
    xor rcx, rcx
    .iter:
        mov ax, word [rdi, rcx * 2]
        cmp al, 0
        je .exit
        check_al_ah ah, .byte_al_letter, .byte_al_num

        .next_ah:
            check_al_ah al, .byte_ah_letter, .byte_ah_num

        .copy_ax:
            or al, ah
            mov byte [rsi, rcx], al
            inc rcx
            jmp .iter
   
    .byte_al_letter:
        copy_byte ah, 0x61, 00001010b, next_ah
        copy_byte ah, 0x62, 00001011b, next_ah
        copy_byte ah, 0x63, 00001100b, next_ah
        copy_byte ah, 0x64, 00001101b, next_ah
        copy_byte ah, 0x65, 00001110b, next_ah
        copy_byte ah, 0x66, 00001111b, next_ah
    .byte_al_num:
        shl ah, 4
        shr ah, 4
        jmp .next_ah

    .byte_ah_letter:
        copy_byte al, 0x61, 10100000b, copy_ax
        copy_byte al, 0x62, 10110000b, copy_ax
        copy_byte al, 0x63, 11000000b, copy_ax
        copy_byte al, 0x64, 11010000b, copy_ax
        copy_byte al, 0x65, 11100000b, copy_ax
        copy_byte al, 0x66, 11110000b, copy_ax
    .byte_ah_num:
        shl al, 4
        jmp .copy_ax

    .exit:
        mov byte [rsi, rcx], 0
        pop rcx
        pop rdx
        ret
