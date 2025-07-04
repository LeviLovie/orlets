#include "interpreter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "lexer.hpp"

int checkForStackElement(std::vector<StackItem> stack, StackItemType type, Token t) {
    if (stack.size() < 2) {
        std::cerr << "Not enought elements on the stack! " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
        exit(1);
    }

    if (stack[stack.size() - 1].Type == type && stack[stack.size() - 2].Type == type) {
        return 1;
    }

    return 0;
}

StackItem getLastStackElement(std::vector<StackItem> *stack, Token t) {
    if (stack->size() < 1) {
        std::cerr << "[INTERPRETER] [ERR]: " << "There is no elements of the stack to get one " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
        exit(1);
    }
    StackItem result =  stack->back();
    stack->pop_back();
    return result;
}

void dump(std::vector<StackItem> *stack, Token t) {
    StackItem dumpItem = getLastStackElement(stack, t);
    switch (dumpItem.Type) {
    case Int:
        std::cout << dumpItem.IntData;
        break;

    case Float:
        std::cout << dumpItem.FloatData;
        break;

    case String:
        std::cout << dumpItem.StringData;
        break;

    default:
        std::cerr << "Unknown StackItemType for Dump: " << t.fileName << ":" << t.line << ":" << t.col << dumpItem.Type << std::endl;
        exit(1);
    }
}

void print(std::vector<StackItem> *stack, Token t) {
    StackItem item = getLastStackElement(stack, t);
    stack->push_back(item);
    switch (item.Type) {
    case Int:
        std::cout << item.IntData;
        break;

    case Float:
        std::cout << item.FloatData;
        break;

    case String:
        std::cout << item.StringData;
        break;

    default:
        std::cerr << "Unknown StackItemType for Dump: " << t.fileName << ":" << t.line << ":" << t.col << item.Type << std::endl;
        exit(1);
    }
}

void checkForSameTypes(StackItem first, StackItem second, Token t) {
    if (first.Type != second.Type) {
        std::cerr << "[INTERPRETER] [ERR]: " << "Different types of values: " << first.Type << " & " << second.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
        exit(1);
    }
}

struct Reg {
    std::string Name;
    int TokenId;
};

int findRegByName(std::vector<Reg> regs, std::string name) {
    for (int i = 0; i < regs.size(); i++) {
        if (regs[i].Name == name) return regs[i].TokenId;
    }
    return -1;
}

std::vector<StackItem> InterpretTokens(std::vector<Token> tokens) {
    std::vector<StackItem> stack;
    std::vector<Reg> regs;

    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        switch (t.Type) {
        case PushInt:
            stack.push_back((StackItem){Int, t.DataInt, 0.0, ""});
            break;

        case PushFloat:
            stack.push_back((StackItem){Float, 0, t.DataFloat, ""});
            break;

        case PushString:
            stack.push_back((StackItem){String, 0, 0.0, t.DataString});
            break;

        case Plus: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData + secondItem.IntData, 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, firstItem.FloatData + secondItem.FloatData, ""});
                break;

            case String:
                stack.push_back((StackItem){String, 0, 0.0, firstItem.StringData + secondItem.StringData});
                break;

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Minus: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData - secondItem.IntData, 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, firstItem.FloatData - secondItem.FloatData, ""});
                break;

            case String:
                std::cerr << "Operation can't be done on strings " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Multiply: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData * secondItem.IntData, 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, firstItem.FloatData * secondItem.FloatData, ""});
                break;

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Divide: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData / secondItem.IntData, 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, firstItem.FloatData / secondItem.FloatData, ""});
                break;

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Power: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, pow(firstItem.IntData, secondItem.IntData), 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, pow(firstItem.FloatData, secondItem.FloatData), ""});
                break;

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Modulo: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData % secondItem.IntData, 0.0, ""});
                break;

            case Float:
                std::cerr << "Operation can't be done on floats" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Swap: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            stack.push_back(secondItem);
            stack.push_back(firstItem);
            break;
        }

        case LSwap: {
            StackItem thirdItem = getLastStackElement(&stack, t);
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            stack.push_back(thirdItem);
            stack.push_back(secondItem);
            stack.push_back(firstItem);
            break;
        }

        case Dup: {
            StackItem item = getLastStackElement(&stack, t);
            stack.push_back(item);
            stack.push_back(item);
            break;
        }

        case Jeg: {
            StackItem item = getLastStackElement(&stack, t);
            if (item.Type != String) {
                std::cerr << "[INTERPRETER] [ERR]: " << "You can registry only string for a jmp " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            if (findRegByName(regs, item.StringData) != -1) {
                std::cerr << "[INTERPRETER] [ERR]: " << "Reg with this name already exists " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            regs.push_back((Reg){item.StringData, i});
            break;
        }

        case Jmp: {
            StackItem item = getLastStackElement(&stack, t);
            if (item.Type != String) {
                std::cerr << "[INTERPRETER] [ERR]: " << "You can use only strings as names for a jmp " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            if (findRegByName(regs, item.StringData) == -1) {
                std::cerr << "[INTERPRETER] [ERR]: " << "Reg with this name is not existng " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            i = findRegByName(regs, item.StringData);
            break;
        }

        case Less: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                if (firstItem.IntData < secondItem.IntData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case Float:
                if (firstItem.FloatData < secondItem.FloatData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case More: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                if (firstItem.IntData > secondItem.IntData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case Float:
                if (firstItem.FloatData > secondItem.FloatData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case String:
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Equal: {
            StackItem secondItem = getLastStackElement(&stack, t);
            StackItem firstItem = getLastStackElement(&stack, t);
            checkForSameTypes(firstItem, secondItem, t);
            switch (firstItem.Type) {
            case Int:
                if (firstItem.IntData == secondItem.IntData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case Float:
                if (firstItem.FloatData == secondItem.FloatData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            case String:
                if (firstItem.StringData == secondItem.StringData) {
                    stack.push_back((StackItem){Int, 1, 0.0, ""});
                } else {
                    stack.push_back((StackItem){Int, 0, 0.0, ""});
                }
                break;

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case If: {
            StackItem item = getLastStackElement(&stack, t);
            switch (item.Type) {
            case Int:
                if (item.IntData == 1) break;
                else {
                    if (t.DataFloat == 0.0) i = t.DataInt;
                    else i = static_cast<int>(t.DataFloat);
                }
                break;

            case Float:
                if (item.FloatData == 1.0f) break;
                else {
                    if (t.DataFloat == 0.0) i = t.DataInt;
                    else i = static_cast<int>(t.DataFloat);
                }
                break;

            case String:
                if (item.StringData == "true") break;
                else {
                    if (t.DataFloat == 0.0) i = t.DataInt;
                    else i = static_cast<int>(t.DataFloat);
                }
                break;

            default:
                std::cerr << "Unknown StackItemType: " << item.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Endif:
            break;

        case Else:
            i = tokens[t.DataInt].DataInt;
            break;

        case Dump:
            dump(&stack, t);
            break;

        case Print:
            print(&stack, t);
            break;

        case Endl:
            std::cout << std::endl;
            break;

        case Debug:
            std::cout << "\x1b[1mDebug stack printout\x1b[0m (in " << t.fileName << ":" << t.line << ":" << t.col << "): ";
            for (int i = 0; i < stack.size(); i++) {
                std::cout << "(" << stack[i].IntData << " " << stack[i].FloatData << " \"" << stack[i].StringData << "\")";
                if (i < stack.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
            break;

        case In: {
            StackItem item = getLastStackElement(&stack, t);
            if (item.Type != String) {
                std::cerr << "[INTERPRETER] [ERR]: " << "You can use only strings as names for a inint " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            std::cout << item.StringData;
            std::string in;
            std::cin >> in;
            // Check if it's a number
            int isNumber = 1;
            for (int i = 0; i < in.size(); i++) {
                if (in[i] < '0' || in[i] > '9') {
                    isNumber = 0;
                    break;
                }
            }
            if (isNumber) {
                // Check if it's a float
                int isFloat = 0;
                for (int i = 0; i < in.size(); i++) {
                    if (in[i] == '.') {
                        isFloat = 1;
                        break;
                    }
                }
                if (isFloat) {
                    stack.push_back((StackItem){Float, 0, std::stof(in), ""});
                } else {
                    stack.push_back((StackItem){Int, std::stoi(in), 0.0, ""});
                }
            } else {
                stack.push_back((StackItem){String, 0, 0.0, in});
            }
            break;
        }

        case Type: {
            StackItem item = getLastStackElement(&stack, t);
            switch (item.Type) {
            case Int:
                stack.push_back((StackItem){String, 0, 0.0, "int"});
                break;
            case Float:
                stack.push_back((StackItem){String, 0, 0.0, "float"});
                break;
            case String:
                stack.push_back((StackItem){String, 0, 0.0, "string"});
                break;
            }
            break;
        }

        default:
            std::cerr << "[INTERPRETER] [ERR]: " << "Unknown token: " << t.Type << std::endl;
            exit(1);
        }
    }

    return stack;
}
