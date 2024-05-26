#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func_shellcode(const char *string, char *shellcode);


int main(int argc, const char **argv)
{   
    if(argc != 2) {
        fprintf(stderr, "Error: function must take one argument\n");
        return 2;
    }

    const char *ptr_string = argv[1];
    size_t leng = strlen(ptr_string);
    size_t shellcode_leng = leng / 2;
    char cheker[] = "0123456789abcdef";
    const char *filename = "shcode.txt";


    if(leng %2 != 0) {
        fprintf(stderr, "Error: wrong string length\n");
        return 2;
    }
    for (size_t i = 0; i < leng; ++i) {
        if (strchr(cheker, ptr_string[i]) == NULL) {
            fprintf(stderr, "Error: string contains invalid characters\n");
            return 2;
        }
    }

    char *shellcode = malloc(shellcode_leng + 1);
    if (shellcode == NULL) {
        perror("Error allocating memory");
        return 1;
    }
    func_shellcode(ptr_string, shellcode);


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
    
    free(shellcode);
    return 0;
}
