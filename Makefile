CFLAGS = -Wall -g
 
 
att:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@gcc $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_att.o -o asm_shellcode_nasm
	@rm form_shellcode.o asm_shellcode_att.o sh

nasm:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o sh
	@rm form_shellcode.o asm_shellcode_nasm.o sh

edb_att:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@gcc $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_att.o -o sh
	@edb --run ./sh eb07909090909090909048b9ff2e70617373776448c1e9084831c05051b002488d3c240f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05
	@rm form_shellcode.o asm_shellcode_att.o sh
edb_nasm:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o sh
	@edb --run ./sh eb07909090909090909048b9ff2e70617373776448c1e9084831c05051b002488d3c240f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05
	@rm form_shellcode.o asm_shellcode_nasm.o sh
run_att:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@gcc $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_att.o -o sh
	@./sh eb07909090909090909048b9ff2e70617373776448c1e9084831c05051b002488d3c240f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05
	@rm form_shellcode.o asm_shellcode_att.o sh
run_nasm:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o sh
	@./sh eb07909090909090909048b9ff2e70617373776448c1e9084831c05051b002488d3c240f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05
	@rm form_shellcode.o asm_shellcode_nasm.o sh

