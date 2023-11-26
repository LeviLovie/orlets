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

                // int lcursor = cursor;
                // while (lcursor < f.size()) {
                //     if (f[lcursor] == '\n') line++;
                //     lcursor++;
                // }
                // lcursor = cursor;
                //
                // bool closeFound = false;
                // int closeParam = lcursor;
                // while (lcursor < f.size() && !closeFound) {
                //     if (f[lcursor] == ')') closeFound = true; closeParam = lcursor;
                //     lcursor++;
                //     col++;
                // }
                // if (!closeFound) {
                //     std::cerr << "[LEXER] [ERR] Can't find closing param for opening param. " << fileName << ":" << linle + 1 << ":" << col << std::endl;
                //     exit(1);
                // }
                // lcursor = cursor;
                //
                // bool isString = false;
                // bool strOpenFound = false;
                // int strOpening = 0;
                // bool closeStringParamFound = false;
                // int closeStringParam = 0;
                // while (lcursor < f.size() && !strOpenFound) {
                //     if (f[lcursor] == '"') {
                //         isString = true;
                //         strOpenFound = true;
                //         strOpening = lcursor;
                //         lcursor++;
                //         while (lcursor < f.size() && !closeStringParamFound) {
                //             if (f[lcursor] == '"') {
                //                 closeStringParamFound = true;
                //                 closeStringParam = lcursor;
                //             }
                //             lcursor++;
                //         }
                //     }
                //     lcursor++;
                // }
                // if (!closeFound) {
                //     std::cerr << "[LEXER] [ERR] Can't find closing string param for opening string param. " << fileName << ":" << strOpening + 1 << ":" << col << std::endl;
                //     exit(1);
                // }
                // lcursor = cursor;
                //
                // if (isString) {
                //     std::string stringData;
                //     int stringLength = closeStringParam - strOpening;
                //     for (int i = 1; i < stringLength; i++) {
                //         stringData += f[i + strOpening];
                //     }
                //     tokens.push_back((Token){PushString, 0, 0.0, stringData, fileName, line + 1, col});
                // } else {
                //     std::string var;
                //     int varLength = closeParam - cursor;
                //     for (int i = 1; i < varLength; i++) {
                //         var += f[i + cursor];
                //     }
                //     var = ltrim(var);
                //     var = rtrim(var);
                //
                //     if (isInteger(var)) {
                //         tokens.push_back((Token){PushInt, stoi(var), 0.0, "", fileName, line + 1, col});
                //     } else if (isFloat(var)) {
                //         tokens.push_back((Token){PushFloat, 0, stof(var), "", fileName, line + 1, col});
                //     }
                // }
            } else {
                col++;
            }
        }
        cursor++;
    }

    return tokens;
}
