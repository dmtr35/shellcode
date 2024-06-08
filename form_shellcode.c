#include "header.h"



int main(int argc, char *argv[])
{   
    if(argc > 3) {
        fprintf(stderr, "Error: function must take one or two arguments\n");
        return 2;
    }

    char *filename;
    char *shellcode;

// ==============================================================

    if (argc == 3) {
        filename = argv[1];
        int check = check_file(argv[2]);
        if (check) {
            handler_file(argv[2], &shellcode);
        } else {
            handler_string(argv[2], &shellcode);
        }
    } else {
        filename = "shcode.txt";
        int check = check_file(argv[1]);
        if (check) {
            handler_file(argv[1], &shellcode);
        } else {
            handler_string(argv[1], &shellcode);
        }
    }

// ==============================================================
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



int check_file(char *file_name) {
    struct stat st = {0};
    if(stat(file_name, &st) == 0) {
        return 1;
    } else {
        return 0;
    }
}

