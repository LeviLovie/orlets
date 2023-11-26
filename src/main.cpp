#include <iostream>
#include <string>
#include <vector>
#include "config.h"
#include "lexer.hpp"
#include "interpreter.hpp"

extern "C" {
    #include "file.h"
}

int main(int argc, char** argv) {
    bootup();
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    if (args.size() < 1) {
        std::cerr << "Please specify file name as first arg" << std::endl;
        exit(1);
    }
    std::string filePath = args[0];
    bool debugMode = false;
    for (int i = 1; i < args.size(); i++) {
        if (args[i] == "-d") debugMode = true;
    }
    if (checkFile(filePath.c_str()) != 1) {
        std::cerr << "File \"" << filePath << "\" not found. Please specify valid filepath!" << std::endl;
        exit(1);
    }

    if (debugMode) {
        std::cout << "\x1b[1mDebug info\x1b[0m:" << std::endl;
    }
    std::string fileData = readFile(filePath.c_str());
    std::vector<Token> tokens = parseFile(fileData, args[1]);
    if (debugMode) {
        for (int i = 0; i < tokens.size(); i++) {
            std::cout << tokens[i].Type << " (" << tokens[i].DataInt << ", " << tokens[i].DataFloat << ", \"" << tokens[i].DataString << "\") " << "in " << tokens[i].fileName << ":" << tokens[i].line << ":" << tokens[i].col << std::endl;
        }
    }
    if (debugMode) {
        std::cout << "\x1b[1mProgramm output\x1b[0m:" << std::endl;
    }

    InterpretTokens(tokens);
}
