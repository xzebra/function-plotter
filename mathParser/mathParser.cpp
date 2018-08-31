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
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        default: // functions
            return 5;           
    }
}

bool assocRight(char c) {
    return c == '^';
}

Operation* Parser::toPostfix(std::string infix) {
    Stack<char> operatorStack = Stack<char>();
    Operation *output = new Operation();
    output->v_pos = std::vector<int>(0);

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
                output->postfix += infix[j]; // push num to the output queue
            }
            output->postfix += ' ';
        } else if(isOperator(c)) {               
            while(!operatorStack.empty()) {
                char head = operatorStack.getHead();
                if(head == '(') break;
                if(precedence(head) < precedence(c)) break;
                if(precedence(head) == precedence(c) && assocRight(head)) break;
                // push operator to the output queue
                output->postfix += operatorStack.pop();
                output->postfix += ' ';
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
                output->postfix += operatorStack.pop();
                output->postfix += ' ';
            }
            if(!found) std::cout << "error: mismatched parenthesis" << std::endl;     
        }
        // TODO: check for functions and variables
    }

    // no more tokens to read:
    while(!operatorStack.empty()) {
        output->postfix += operatorStack.pop();
        output->postfix += ' ';
    }

    return output;
}

double Parser::Solve(const std::string postfix) {
    Stack<double> operandStack = Stack<double>();
    std::stringstream ss(postfix);
    std::string token;
    
    while(ss >> token) { // iterate through each token in string    
        if(isNum(token[0])) { 
            // if number push to stack
            operandStack.push(std::stoi(token));
        } else { // is operator -> solve that operation
            // pop the last two numbers
            double y = operandStack.pop(), x = operandStack.pop();
            // push result to stack      
            switch (token[0]) {
                case '+':                   
                    operandStack.push(x + y);
                    break;
                case '-':
                    operandStack.push(x - y);
                    break;
                case '*':
                    operandStack.push(x * y);
                    break;
                case '/':
                    operandStack.push(x / y);
                    break;
                case '^':
                    operandStack.push(std::pow(x, y));
                    break;
            }            
        }
    }

    // pop result from stack
    return operandStack.pop();
}

