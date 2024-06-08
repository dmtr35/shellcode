#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <gelf.h>


// form_shellcode.c:
void func_shellcode(char *string, char *shellcode);
int check_file(char *file_name);

// handler_string.c:
void handler_string(char *string, char **shellcode);
void copy_arr(char *shellcode, char *buf, int *count);
void write_to_buffer(size_t leng_str, char **string, char *buf);

// handler_file.c:
void handler_file(char *arg, char **shellcode);



#endif



