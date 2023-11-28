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

void dumpInt(std::vector<StackItem> *stack, Token t) {
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
    std::cout << " ";
}

void checkForSameTypes(StackItem first, StackItem second, Token t) {
    if (first.Type != second.Type) {
        std::cerr << "[INTERPRETER] [ERR]: " << "Different types of values: " << first.Type << " & " << second.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
        exit(1);
    }
}

std::vector<StackItem> InterpretTokens(std::vector<Token> tokens) {
    std::vector<StackItem> stack;

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
            stack.push_back(firstItem);
            stack.push_back(secondItem);
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
                std::cerr << "Operation can't be done on strings" << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);

            default:
                std::cerr << "Unknown StackItemType: " << firstItem.Type << " in " << t.fileName << ":" << t.line << ":" << t.col << std::endl;
                exit(1);
            }
            break;
        }

        case Dump:
            dumpInt(&stack, t);
            break;

        case Endl:
            std::cout << std::endl;
            break;

        case Debug:
            std::cout << "\x1b[1mDebug stack printout\x1b[0m (in " << t.fileName << ":" << t.line << ":" << t.col << "): ";
            for (int i = 0; i < stack.size(); i++) {
                if (stack[i].Type == Int) {
                    std::cout << stack[i].IntData;
                } else if (stack[i].Type == Float) {
                    std::cout << stack[i].FloatData;
                } else if (stack[i].Type == String) {
                    std::cout << "\"" << stack[i].StringData << "\"";
                }
                if (i < stack.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        break;

        default:
            std::cerr << "[INTERPRETER] [ERR]: " << "Unknown token: " << t.Type << std::endl;
            exit(1);
        }
    }

    return stack;
}
