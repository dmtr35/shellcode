#include "header.h"


void handler_string(char *string, char **shellcode)
{
    char cheker[] = "0123456789abcdefABCDEF";
    size_t leng_str = strlen(string) + 1;
    
    int count = 0;
    _Bool flag = 0;

    *shellcode = malloc((leng_str) * sizeof(char));
    if (*shellcode == NULL) {
        perror("Error allocating memory");
        return;
    }
    
    while(*string) {
        if(*string == '\'') {
            flag = !flag;
            string++;
        }

        if(*string == '\0') {
            return;
        }

        if(flag) {
            char *buf = malloc(leng_str);
            if (*shellcode == NULL) {
                perror("Error allocating memory");
                exit(EXIT_SUCCESS);
            }
            write_to_buf(leng_str, &string, buf, flag);

            copy_arr(*shellcode, buf, &count);
            free(buf);
        } else {
            char *ptr_shellcode = *shellcode + count;
            
            char *buf = malloc(leng_str);
            if (*shellcode == NULL) {
                perror("Error allocating memory");
                exit(EXIT_SUCCESS);
            }
            write_to_buf(leng_str, &string, buf, flag);

            size_t leng = strlen(buf);
            if(leng %2 != 0) {
                fprintf(stderr, "Error: wrong string length\n");
                exit(EXIT_SUCCESS);
            }
            for (size_t i = 0; i < leng; ++i) {
                if (strchr(cheker, buf[i]) == NULL) {
                    fprintf(stderr, "Error: string contains invalid characters\n");
                    exit(EXIT_SUCCESS);
                }
            }

            func_shellcode(buf, ptr_shellcode);

            count += leng / 2;
            free(buf);
        }
    }
}


void copy_arr(char *shellcode, char *buf, int *count)
{
    size_t leng = strlen(buf);
    for(int i = 0; i < leng; ++i) {
        shellcode[*count] = buf[i];
        (*count)++;
    }
    shellcode[*count] = '\0';
}


void write_to_buf(size_t leng_str, char **string, char *buf, _Bool flag)
{
    int i = 0;
    while(**string != '\'' && **string != '\0') {
        if (!flag && (**string == 'x' || **string == 'X' || **string == '\\' || **string == ' ')) {
            (*string)++;
            continue;
        }
        buf[i] = **string;
        i++;
        (*string)++;
    }
    buf[i] = '\0';
}

