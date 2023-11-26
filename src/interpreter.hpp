#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include "lexer.hpp"

enum StackItemType {
    Int, Float, String
};

struct StackItem {
    StackItemType Type;
    int IntData;
    float FloatData;
    std::string StringData;
};

std::vector<StackItem> InterpretTokens(std::vector<Token> tokens);

#endif // INTEPRETER_HPP
