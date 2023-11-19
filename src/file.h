#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>

int checkFile(const char* path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
};

const char* readFile(const char* path) {
    FILE *file;
    file = fopen(path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);

    return content;
}

#endif // FILE_H_
