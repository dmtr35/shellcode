CFLAGS = -Wall -g
 
 
att:
	@gcc -Wall -g -c form_shellcode.c -o form_shellcode.o && gcc -Wall -g -c asm_shellcode_att.s -o asm_shellcode_att.o && gcc -Wall -g form_shellcode.o asm_shellcode_att.o -o shcode
	@rm form_shellcode.o asm_shellcode_att.o

nasm:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o shcode
	@rm form_shellcode.o asm_shellcode_nasm.o

# edb_att:
# 	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
# 	@gcc $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
# 	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_att.o -o shcode
# 	@edb --run ./shcode eb079090909090909090eb005f51b0024831f60f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05e8ccffffff24484f4d452f2e70617373776400
# 	@rm form_shellcode.o asm_shellcode_att.o
# edb_nasm:
# 	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
# 	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
# 	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o shcode
# 	@edb --run ./shcode eb079090909090909090eb005f51b0024831f60f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05e8ccffffff24484f4d452f2e70617373776400
# 	@rm form_shellcode.o asm_shellcode_nasm.o
run_att:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@gcc $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_att.o -o shcode
	@./shcode eb079090909090909090eb005f51b0024831f60f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05e8ccffffff24484f4d452f2e706173737764
	@rm form_shellcode.o asm_shellcode_att.o
run_nasm:
	@gcc $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@nasm -felf64 asm_shellcode_nasm.s -o asm_shellcode_nasm.o
	@gcc $(CFLAGS) form_shellcode.o asm_shellcode_nasm.o -o shcode
	@./shcode eb079090909090909090eb005f51b0024831f60f054889c74883ec0f488d34244831d2b20f4831c00f05b00140b701488d3424b20f0f05b03c0f05e8ccffffff24484f4d452f2e706173737764
	@rm form_shellcode.o asm_shellcode_nasm.o

