#include "interpreter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "lexer.hpp"

int checkForStackElement(std::vector<StackItem> stack, StackItemType type) {
    if (stack.size() < 2) {
        std::cerr << "Not enought elements on the stack!" << std::endl;
        exit(1);
    }

    if (stack[stack.size() - 1].Type == type && stack[stack.size() - 2].Type == type) {
        return 1;
    }

    return 0;
}

StackItem getLastStackElement(std::vector<StackItem> *stack) {
    if (stack->size() < 1) {
        std::cerr << "[INTERPRETER] [ERR]: " << "There is no elements of the stack to get one" << std::endl;
        exit(1);
    }
    StackItem result =  stack->back();
    stack->pop_back();
    return result;
}

void dumpInt(std::vector<StackItem> *stack) {
    StackItem dumpItem = getLastStackElement(stack);
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
        std::cerr << "Unknown StackItemType for Dump: " << dumpItem.Type << std::endl;
        exit(1);
    }
    std::cout << " " << std::endl;
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
            StackItem firstItem = getLastStackElement(&stack);
            StackItem secondItem = getLastStackElement(&stack);
            if (firstItem.Type != secondItem.Type) {
                std::cerr << "[INTERPRETER] [ERR]: " << "Different types of values for Plus: " << firstItem.Type << " & " << secondItem.Type << std::endl;
                exit(1);
            }
            switch (firstItem.Type) {
            case Int:
                stack.push_back((StackItem){Int, firstItem.IntData + secondItem.IntData, 0.0, ""});
                break;

            case Float:
                stack.push_back((StackItem){Float, 0, firstItem.FloatData + secondItem.FloatData, ""});
                break;

            case String:
                stack.push_back((StackItem){String, 0, 0.0, secondItem.StringData + firstItem.StringData});
                break;

            default:
                std::cerr << "Unknown StackItemType for Plus: " << firstItem.Type << std::endl;
                exit(1);
            }
            break;
        }

        case Dump:
            dumpInt(&stack);
            break;

        default:
            std::cerr << "[INTERPRETER] [ERR]: " << "Unknown token: " << t.Type << std::endl;
            break;
        }
    }

    return stack;
}
