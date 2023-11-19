#include "lexer.hpp"
#include <iostream>
#include <string>
#include <vector>

void ParseNext(std::string fileData, std::vector<Token>* tokens, Cursor* cursor) {
    Token result;

    result.DataString = fileData[cursor->Index];

    cursor->Index++;
    tokens->push_back(result);
}
