#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func_shellcode(char *string, char *shellcode);
void handler_string(const char *string, char *shellcode);
void copy_arr(char *shellcode, char *buf, int *count);
void write_to_buffer(size_t leng_str, const char **string, char *buf);

int main(int argc, const char **argv)
{   
    if(argc != 2) {
        fprintf(stderr, "Error: function must take one argument\n");
        return 2;
    }

    const char *filename = "shcode.txt";
    size_t leng = strlen(argv[1]);
    const char *string = argv[1];
    char *shellcode = malloc((leng + 1) * sizeof(char));
    if (shellcode == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    handler_string(string, shellcode);
    size_t shellcode_leng = strlen(shellcode);


    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    size_t written = fwrite(shellcode, sizeof(char), shellcode_leng, file);
    if (written != shellcode_leng) {
        perror("Error writing to file");
        fclose(file);
        free(shellcode);
        return 1;
    }

    if (fclose(file) != 0) {
        perror("Error closing file");
        return 1;
    }

    printf("bytes: %ld\n", shellcode_leng);
    
    free(shellcode);
    return 0;
}


void handler_string(const char *string, char *shellcode)
{
    char cheker[] = "0123456789abcdefABCDEF";
    size_t leng_str = strlen(string) + 1;
    
    int count = 0;
    _Bool flag = 0;
    
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
            if (shellcode == NULL) {
                perror("Error allocating memory");
                exit(EXIT_SUCCESS);
            }
            write_to_buffer(leng_str, &string, buf);

            copy_arr(shellcode, buf, &count);
            free(buf);
        } else {
            char *ptr_shellcode = shellcode + count;
            
            char *buf = malloc(leng_str);
            if (shellcode == NULL) {
                perror("Error allocating memory");
                exit(EXIT_SUCCESS);
            }
            write_to_buffer(leng_str, &string, buf);

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

void write_to_buffer(size_t leng_str, const char **string, char *buf)
{
    int i = 0;
    while(**string != '\'' && **string != '\0') {
        buf[i] = **string;
        i++;
        (*string)++;
    }
    buf[i] = '\0';
}