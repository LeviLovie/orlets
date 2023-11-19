#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>

enum TokenType {
    StackPush, Print
};

struct Cursor {
    int Index;
};

struct Token {
    TokenType Type;
    int DataInt;
    std::string DataString;
    Token* tokens[];
};

Token ParseNext(std::string fileData);

#endif // LEXER_HPP_
