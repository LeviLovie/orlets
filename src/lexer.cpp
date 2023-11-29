#include "lexer.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.compare(0, prefix.length(), prefix) == 0;
}

bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool isInteger(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isFloat(const std::string &s) {
    std::istringstream iss(s);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

bool checkForSpaceToken(std::string str, int cursor, char token) {
    return str[cursor] == token && (str[cursor + 1] == ' ' || str[cursor + 1] == '\n' || cursor == str.size() - 1);
}

std::string ltrim(const std::string& s) {
    size_t start = 0;
    while (start < s.length() && std::isspace(s[start])) {
        start++;
    }

    return s.substr(start);
}

std::string rtrim(const std::string& s) {
    size_t end = s.length();
    while (end > 0 && std::isspace(s[end - 1])) {
        end--;
    }

    return s.substr(0, end);
}

std::vector<Token> parseFile(std::string f, std::string fileName) {
    std::vector<Token> tokens;
    int line = 0;
    int col = 0;
    int cursor = 0;

    bool insideVarScope = false;
    while (cursor < f.size()) {
        if (f[cursor] == ' ') {
            col++;
        } else  {
            if (f[cursor] == '\n') {
                line++;
                col = 0;
            } else if (checkForSpaceToken(f, cursor, '+')) {
                tokens.push_back((Token){Plus, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '.')) {
                tokens.push_back((Token){Dump, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, ',')) {
                tokens.push_back((Token){Print, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '-')) {
                tokens.push_back((Token){Minus, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '*')) {
                tokens.push_back((Token){Multiply, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '/')) {
                tokens.push_back((Token){Divide, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '^')) {
                tokens.push_back((Token){Power, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '%')) {
                tokens.push_back((Token){Modulo, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '<')) {
                tokens.push_back((Token){Less, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '>')) {
                tokens.push_back((Token){More, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '=')) {
                tokens.push_back((Token){Equal, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (checkForSpaceToken(f, cursor, '`')) {
                tokens.push_back((Token){Debug, 0, 0.0, "", fileName, line + 1, col});
                col++;
            } else if (f[cursor] == '(') {
                int lc = cursor + 1;
                std::string varstr = "";
                while (lc < f.size()) {
                    if (f[lc] == ')' && f[lc - 1] != '\\') {
                        col++;
                        break;
                    } else if (f[lc] == '\n') {
                        line++;
                        col = 0;
                    } else {
                        varstr += f[lc];
                    }
                    lc++;
                }
                cursor = lc;
                if (varstr == "") {
                    std::cerr << "[LEXER] [ERR] Params aren't closed or have no value " << fileName << ":" << line + 1 << ":" << col << std::endl;
                    exit(1);
                }
                for (size_t i = 0; i < varstr.length(); ++i) {
                    if (varstr[i] == '\\' && (i == 0 || varstr[i - 1] != '\\')) {
                        varstr.erase(i, 1);
                        --i;
                    }
                }
                varstr = rtrim(ltrim(varstr));

                if (isInteger(varstr)) {
                    tokens.push_back((Token){PushInt, stoi(varstr), 0.0, "", fileName, line + 1, col});
                } else if (isFloat(varstr)) {
                    tokens.push_back((Token){PushFloat, 0, stof(varstr), "", fileName, line + 1, col});
                } else if (startsWith(varstr, "\"") && endsWith(varstr, "\"")) {
                    tokens.push_back((Token){PushString, 0, 0.0, varstr.substr(1, varstr.length() - 2), fileName, line + 1, col});
                } else {
                    std::cerr << "[LEXER] [ERR] Can't parse valuse inside params (wrap strings in \"\") " << fileName << ":" << line + 1 << ":" << col << std::endl;
                    exit(1);
                }
            } else if (startsWith(f.substr(cursor, f.size()), "//")) {
                int lc = cursor;
                while(lc < f.size()) {
                    if (f[lc] == '\n') break;
                    lc++;
                }
                cursor = lc;
                line++;
                col = 0;
            } else if (startsWith(f.substr(cursor, f.size()), "endl")) {
                tokens.push_back((Token){Endl, 0, 0.0, "", fileName, line + 1, col});
                cursor += 3;
                col += 4;
            } else if (startsWith(f.substr(cursor, f.size()), "if")) {
                tokens.push_back((Token){If, 0, 0.0, "", fileName, line + 1, col});
                cursor++;
                col += 1;
            } else if (startsWith(f.substr(cursor, f.size()), "endif")) {
                tokens.push_back((Token){Endif, 0, 0.0, "", fileName, line + 1, col});
                cursor += 4;
                col += 5;
            } else if (startsWith(f.substr(cursor, f.size()), "swp")) {
                tokens.push_back((Token){Swap, 0, 0.0, "", fileName, line + 1, col});
                cursor += 2;
                col += 3;
            } else if (startsWith(f.substr(cursor, f.size()), "lswp")) {
                tokens.push_back((Token){LSwap, 0, 0.0, "", fileName, line + 1, col});
                cursor += 3;
                col += 4;
            } else if (startsWith(f.substr(cursor, f.size()), "dup")) {
                tokens.push_back((Token){Dup, 0, 0.0, "", fileName, line + 1, col});
                cursor += 2;
                col += 3;
            } else if (startsWith(f.substr(cursor, f.size()), "jeg")) {
                tokens.push_back((Token){Jeg, 0, 0.0, "", fileName, line + 1, col});
                cursor += 2;
                col += 3;
            } else if (startsWith(f.substr(cursor, f.size()), "jmp")) {
                tokens.push_back((Token){Jmp, 0, 0.0, "", fileName, line + 1, col});
                cursor += 2;
                col += 3;
            } else if (startsWith(f.substr(cursor, f.size()), "else")) {
                tokens.push_back((Token){Else, 0, 0.0, "", fileName, line + 1, col});
                cursor += 3;
                col += 4;
            } else {
                col++;
            }
        }
        cursor++;
    }

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].Type == If) {
            int lc = i;
            int depth = 0;
            while (lc < tokens.size()) {
                lc++;

                if (tokens[lc].Type == If) depth++;
                else if (tokens[lc].Type == Endif) {
                    if (depth == 0) {
                        tokens[i].DataInt = lc;
                    } else depth--;
                    if (depth < 0) {
                        std::cerr << "[LEXER] [ERR] Too many \"endif\" tokens " << tokens[lc].fileName << ":" << tokens[lc].line + 1 << ":" << tokens[lc].col << std::endl;
                        exit(1);
                    }
                } else if (tokens[lc].Type == Else) {
                    if (depth == 0) {
                        tokens[i].DataFloat = static_cast<float>(lc);
                        tokens[lc].DataInt = i;
                    }
                }

                if (lc == tokens.size() + 1) {
                    std::cerr << "[LEXER] [ERR] Can't find \"endif\" token for " << tokens[i].fileName << ":" << tokens[i].line + 1 << ":" << tokens[i].col << std::endl;
                    exit(1);
                }
            }
        }
    }

    return tokens;
}
