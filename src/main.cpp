#include <iostream>
#include <string>
#include <vector>
#include "config.h"
#include "lexer.hpp"

extern "C" {
    #include "file.h"
}

int main(int argCount, char** args) {
    bootup();

    if (argCount < 2) {
        std::cerr << "Please specify file path!" << std::endl;
        exit(1);
    }

    std::string filePath;
    filePath = args[1];
    if (checkFile(filePath.c_str()) != 1) {
        std::cerr << "File \"" << filePath << "\" not found. Please specify valid filepath!" << std::endl;
        exit(1);
    } else {
        std::cout << "Intepreting \"" << filePath << "\";" << std::endl;
    }

    std::string fileData;
    fileData = readFile(filePath.c_str());
    fileData = removeNewLines(fileData.c_str());

    std::vector<Token> tokens;
    Cursor cursor = {0};
    while (cursor.Index < fileData.size()) {
        ParseNext(fileData, &tokens, &cursor);
    }

    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].DataString << " ";
    }
    std::cout << std::endl;
}
