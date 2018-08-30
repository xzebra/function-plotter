#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <iostream>
#include <string>

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
        std::string toPostfix(std::string infix);
};

#endif