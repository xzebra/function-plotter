#include "mathParser.h"
#include "stack.h"

bool isNum(const char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
            return true;
    }
    return false;
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 2;
            break;
        case '*':
        case '/':
            return 3;
            break;
        case '^':
            return 4;
            break;
    }
}

bool assocRight(char c) {
    return c == '^';
}

std::string Parser::toPostfix(std::string infix) {
    Stack<char> operatorStack = Stack<char>();
    std::string postfix = "";

    // While there are tokens to be read
    for(int i = 0; i < infix.length(); i++) {
        char c = infix[i]; // Read a token
        if(c == ' ') continue;
        if(isNum(c)) { // token is number
            for(int j = i; j < infix.length(); j++) {
                // parse its digits // TODO: double nums
                if(!isNum(infix[j])) {
                    i = j-1;
                    break;
                }               
                postfix += c; // push num to the output queue
            }
            postfix += ' ';
        } else if(isOperator(c)) {               
            while(!operatorStack.empty()) {
                char head = operatorStack.getHead();
                if(head == '(') break;
                if(precedence(head) < precedence(c)) break;
                if(precedence(head) == precedence(c) && assocRight(head)) break;
                // push operator to the output queue
                postfix += operatorStack.pop();
                postfix += ' ';
            }            
            operatorStack.push(c);

        } else if(c == ')') {
            bool found = false;
            while(!operatorStack.empty()) {
                // while the operator at the top of the stack is not a left
                // bracket -> pop the operator from stack onto the output
                if(operatorStack.getHead() == '(') {
                    // pop the left bracket from the stack
                    operatorStack.pop();
                    found = true;
                    break;
                }
                postfix += operatorStack.pop();
                postfix += ' ';
            }
            if(!found) std::cout << "error: mismatched parenthesis" << std::endl;     
        }
        // TODO: check for functions and variables
    }

    // no more tokens to read:
    while(!operatorStack.empty()) {
        postfix += operatorStack.pop();
        postfix += ' ';
    }

    return postfix;
}

Operation Parser::Parse(std::string infix) {
    Stack operatorStack = Stack<char>();
    Stack outputStack = Stack<Operation>();
    std::string postfix = "";

    // While there are tokens to be read
    for(int i = 0; i < infix.length(); i++) {
        char c = infix[i]; // Read a token
        if(c == ' ') continue;
        if(isNum(c)) { // token is number
            for(int j = i; j < infix.length(); j++) {
                // parse its digits // TODO: double nums
                if(!isNum(infix[j])) {
                    i = j-1;
                    break;
                }               
                postfix += c; // push num to the output queue
            }
            postfix += ' ';
        } else if(isOperator(c)) {               
            while(!operatorStack.empty()) {
                char head = operatorStack.getHead();
                if(head == '(') break;
                if(precedence(head) < precedence(c)) break;
                if(precedence(head) == precedence(c) && assocRight(head)) break;
                // push operator to the output queue
                postfix += operatorStack.pop();
                postfix += ' ';
            }            
            operatorStack.push(c);

        } else if(c == ')') {
            bool found = false;
            while(!operatorStack.empty()) {
                // while the operator at the top of the stack is not a left
                // bracket -> pop the operator from stack onto the output
                if(operatorStack.getHead() == '(') {
                    // pop the left bracket from the stack
                    operatorStack.pop();
                    found = true;
                    break;
                }
                postfix += operatorStack.pop();
                postfix += ' ';
            }
            if(!found) std::cout << "error: mismatched parenthesis" << std::endl;     
        }
        // TODO: check for functions and variables
    }

    // no more tokens to read:
    while(!operatorStack.empty()) {
        postfix += operatorStack.pop();
        postfix += ' ';
    }

    return postfix;
}