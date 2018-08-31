#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct Operation {
    std::string postfix; // postfix interpretation of the expression
    std::vector<int> variables; // indexes of variables
};

class Parser {
    public:
        Parser() = default;
        ~Parser() = default;
        double Solve(const std::string op);
        Operation* toPostfix(std::string infix);
};

#endif