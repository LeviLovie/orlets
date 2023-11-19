#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <vector>

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

void ParseNext(std::string fileData, std::vector<Token>* tokens, Cursor* cursor);

#endif // LEXER_HPP_
