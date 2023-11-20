#include "lexer.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> result;
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

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

std::vector<Token> parseFile(std::string fileData) {
    std::vector<Token> result;
    std::vector<std::string> tokens = splitString(fileData);
    for (int i = 0; i < tokens.size(); i++) {
        std::string t = tokens[i];
        Token token;
        token.DataInt = 0;
        token.DataString = "";

        if (t == "+") {
            token.Type = Plus;
        } else if (t == ".") {
            token.Type = Dump;
        } else if (startsWith(t, "(") && endsWith(t, ")")) {
            std::string sbstr = t.substr(1, t.length() - 2);
            if (isInteger(sbstr)) {
                token.Type = PushInt;
                token.DataInt = stoi(sbstr);
            } else if (isFloat(sbstr)) {
                token.Type = PushFloat;
                token.DataString = sbstr;
            } else {
                token.Type = PushString;
                token.DataString = sbstr;
            }
        } else {
            std::cerr << "Not implemented token: \"" << t << "\"" << std::endl;
        }

        result.push_back(token);
    }

    return result;
}
