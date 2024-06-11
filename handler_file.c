#include "header.h"



void handler_file(char *arg, char **shellcode) {
    char *section_name = ".text";
    Elf_Data *data;


    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    int fd = open(arg, O_RDONLY, 0);
    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    Elf *e = elf_begin(fd, ELF_C_READ, NULL);
    if (!e) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t shstrndx;
    if (elf_getshdrstrndx(e, &shstrndx) != 0) {
        fprintf(stderr, "elf_getshdrstrndx() failed: %s\n", elf_errmsg(-1));
        elf_end(e);
        close(fd);
        exit(EXIT_FAILURE);
    }

    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    while ((scn = elf_nextscn(e, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "gelf_getshdr() failed: %s\n", elf_errmsg(-1));
            elf_end(e);
            close(fd);
            exit(EXIT_FAILURE);
        }

        char *name = elf_strptr(e, shstrndx, shdr.sh_name);
        if (name && strcmp(name, section_name) == 0) {
            data = elf_getdata(scn, NULL);
            if (!data) {
                fprintf(stderr, "elf_getdata() failed: %s\n", elf_errmsg(-1));
                elf_end(e);
                close(fd);
                exit(EXIT_FAILURE);
            }
            break;
        }
    }

    size_t data_size = data->d_size;
    *shellcode = malloc(data_size + 1);
    if (*shellcode == NULL) {
        fprintf(stderr, "Failed to allocate memory for string\n");
        elf_end(e);
        close(fd);
        exit(EXIT_FAILURE);
    }

    memcpy(*shellcode, data->d_buf, data_size);
    (*shellcode)[data_size] = '\0';


    elf_end(e);
    close(fd);
}


