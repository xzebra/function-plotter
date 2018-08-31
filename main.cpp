#include <iostream>
//#include "plot.h"
#include "mathParser/mathParser.h"

/*
double function1(double x, double t) {
    return 0.1*cos(8*3.1416*t - 4*3.1416*x);
}
*/

int main() {
    Parser mathParser = Parser();
    std::string input;
    std::getline(std::cin, input);
    Operation *op = mathParser.toPostfix(input);
    //std::cout << op->postfix << std::endl;
    std::cout << mathParser.Solve(op->postfix) << std::endl;
    /*Graph<double> graph(15, 1.0/20); //size | step

    //Example 1
    std::cout << "\e[0;32mSTATIC EXAMPLE:\e[0m" << std::endl;
    //graph.fillValues(1, &function1);
    graph.fillValues(2, &function2);
    graph.plot();
    graph.clearMemory();*/

    //Example 2
    /*
    std::cout << "\n\n" << "\e[0;32mANIMATED EXAMPLE:\e[0m" << std::endl;
    graph.loop(&function2);
    graph.clearMemory();*/  
}