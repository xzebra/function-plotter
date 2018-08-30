#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <iostream>
#include <string>
#include "stack.h"

struct Operation {
    char op;
    double result;
    Operation *x, *y;
};

class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        Operation Parse(std::string input);
    private:
        Stack<double> operandStack;
        Stack<char> operatorStack;
};

#endif