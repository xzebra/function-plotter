#include "mathParser.h"
#include "stack.h"

bool isNum(const char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(const char c) {
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

bool isLetter(const char c) {
    return c >= 'a' && c <= 'z';
}

bool isFunc(int &i, std::string &infix, std::string &output) {
    output = "";
    for(; i < infix.length(); i++) {
        if(!isLetter(infix[i])) {
            i--;
            break;
        }
        output += infix[i];
    }

    return output.length() > 1;
}

int precedence(const char c) {
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

bool assocRight(const char c) {
    return c == '^';
}

Operation* Parser::toPostfix(std::string infix) {
    Stack<std::string> operatorStack = Stack<std::string>();
    Operation *output = new Operation();
    output->v_pos = std::vector<int>(0);

    std::string funcName_temp;

    // While there are tokens to be read
    for(int i = 0; i < infix.length(); i++) {
        char c = infix[i]; // Read a token
        if(c == ' ') continue;
        if(isNum(c)) { // token is number
            // check if number is negative and not substracting
            bool negative = false;
            if(i == 1 && infix[i-1] == '-' || i > 1 && infix[i-1] == '-' && !isNum(infix[i-2])) {
                output->postfix += std::string(1, '-');
            }

            for(; i < infix.length(); i++) {
                // parse its digits
                if(!isNum(infix[i]) && infix[i] != '.') {
                    i--;
                    break;
                }            
                output->postfix += std::string(1, infix[i]); // push num to the output queue
            }
            output->postfix += ' ';
        } else if(c == ')') {
            bool found = false;
            while(!operatorStack.empty()) {
                // while the operator at the top of the stack is not a left
                // bracket -> pop the operator from stack onto the output
                if(operatorStack.getHead()[0] == '(') {
                    // pop the left bracket from the stack
                    operatorStack.pop();
                    found = true;
                    break;
                }
                output->postfix += operatorStack.pop();
                output->postfix += ' ';
            }
            if(!found) std::cout << "error: mismatched parenthesis" << std::endl;     
        } else if(isOperator(c) || isFunc(i, infix, funcName_temp)) {
            bool func = funcName_temp.length() > 1;
            if(!func && c == '-') {
                // check if substracting or is the negative sign of a number
                if(!i) continue;
                if(isOperator(infix[i-1])) continue;                    
                if((i-2) >= 0) {
                    if(isLetter(infix[i-1]) && isLetter(infix[i-2])) continue;
                    // else -> is variable
                }
            }
            while(!operatorStack.empty()) {
                std::string head = operatorStack.getHead();
                if(c == '(' || head[0] == '(') break;
                if(func) break;
                if(precedence(head[0]) < precedence(c)) break;
                if(precedence(head[0]) == precedence(c) && assocRight(head[0])) break;
                // push operator to the output queue
                output->postfix += operatorStack.pop();
                output->postfix += ' ';
            }
            if(func) {
                operatorStack.push(funcName_temp);
                funcName_temp = "";
            } else operatorStack.push(std::string(1, c));

        } else { // variable
            output->postfix += c;
            output->postfix += ' ';
            output->v_pos.push_back(output->postfix.length()-2);
            output->v_values.push_back(0);
        }
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
        if(isNum(token[0]) || token.length() > 1 && token[0] == '-') { //starts with -  
            // if number push to stack
            operandStack.push(std::stod(token));
        } else { // is operator -> solve that operation
            double y = operandStack.pop();
            // push result to stack      
            switch (token[0]) {
                case '+':    
                    operandStack.push(operandStack.pop() + y);
                    continue;
                case '-':
                    operandStack.push(operandStack.pop() - y);
                    continue;
                case '*':
                    operandStack.push(operandStack.pop() * y);
                    continue;
                case '/':
                    operandStack.push(operandStack.pop() / y);
                    continue;
                case '^':
                    operandStack.push(std::pow(operandStack.pop(), y));
                    continue;
            }
            if(token == "sin") {               
                operandStack.push(std::sin(y));
            } else if(token == "cos") {
                operandStack.push(std::cos(y));
            } else if(token == "tan") {
                operandStack.push(std::tan(y));
            }         
        }
    }

    // pop result from stack
    return operandStack.pop();
}

