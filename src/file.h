#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>

int checkFile(const char* path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
};

#endif // FILE_H_
