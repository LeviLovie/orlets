#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

const char* cleanFile(const char* data) {
    if (data == NULL) {
        return NULL;
    }

    int len = 0;
    int consecutiveWhitespace = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        if (isspace((unsigned char)data[i])) {
            if (consecutiveWhitespace == 0) {
                len++;
            }
            consecutiveWhitespace = 1;
        } else {
            len++;
            consecutiveWhitespace = 0;
        }
    }

    char* cleanedData = (char*)malloc(len + 1);
    if (cleanedData == NULL) {
        return NULL;
    }

    int index = 0;
    consecutiveWhitespace = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        if (isspace((unsigned char)data[i])) {
            if (consecutiveWhitespace == 0) {
                cleanedData[index++] = ' ';
            }
            consecutiveWhitespace = 1;
        } else {
            cleanedData[index++] = data[i];
            consecutiveWhitespace = 0;
        }
    }

    cleanedData[index] = '\0';
    return cleanedData;
}

#endif // FILE_H_
