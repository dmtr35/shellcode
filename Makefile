CC = gcc
CFLAGS = -Wall -g
 
all:
	@$(CC) $(CFLAGS) -c form_shellcode.c -o form_shellcode.o
	@$(CC) $(CFLAGS) -c handler_file.c -o handler_file.o -lelf
	@$(CC) $(CFLAGS) -c handler_string.c -o handler_string.o
	@$(CC) $(CFLAGS) -c asm_shellcode_att.s -o asm_shellcode_att.o
	@$(CC) $(CFLAGS) form_shellcode.o handler_file.o handler_string.o asm_shellcode_att.o -o shcode -lelf
	@rm -rf *.o




