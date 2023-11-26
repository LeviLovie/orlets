#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <vector>

enum TokenType {
    PushInt, PushFloat, PushString,
    Plus, Minus, Multiply, Divide, Power, Modulo,
    Swap, Dump, Less, More, Equal,
};

struct Token {
    TokenType Type;
    int DataInt;
    float DataFloat;
    std::string DataString;
};

std::vector<Token> parseFile(std::string fileData);

#endif // LEXER_HPP_
