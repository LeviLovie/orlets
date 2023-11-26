#include <iostream>
#include <string>
#include <vector>
#include "config.h"
#include "lexer.hpp"
#include "interpreter.hpp"

extern "C" {
    #include "file.h"
}

int main(int argCount, char** args) {
    bootup();

    if (argCount < 2) {
        std::cerr << "Please specify file path!" << std::endl;
        exit(1);
    }

    std::string filePath = args[1];
    if (checkFile(filePath.c_str()) != 1) {
        std::cerr << "File \"" << filePath << "\" not found. Please specify valid filepath!" << std::endl;
        exit(1);
    }

    std::string fileData = cleanFile(readFile(filePath.c_str()));
    std::vector<Token> tokens = parseFile(fileData);

    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].Type << " (" << tokens[i].DataInt << ", " << tokens[i].DataFloat << ", \"" << tokens[i].DataString << "\")" << std::endl;
    }

    InterpretTokens(tokens);
}
