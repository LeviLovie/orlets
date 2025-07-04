#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <vector>

enum TokenType {
    PushInt, PushFloat, PushString,
    Plus, Minus, Multiply, Divide, Power, Modulo,
    Swap, LSwap, Dump, Print, Less, More, Equal, Debug, Endl, Dup,
    Jeg, Jmp, If, Endif, Else,
    Type, In,
};

struct Token {
    TokenType Type;
    int DataInt;
    float DataFloat;
    std::string DataString;
    std::string fileName;
    int line;
    int col;
};

std::vector<Token> parseFile(std::string fileData, std::string fileName);

#endif // LEXER_HPP_
