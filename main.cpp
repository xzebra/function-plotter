#include <iostream>
#include "plot.h"

/*
double function1(double x, double t) {
    return 0.1*cos(8*3.1416*t - 4*3.1416*x);
}
*/

int main() {
    Parser mathParser = Parser();
    std::string input;
    std::getline(std::cin, input);
    
    //Graph graph(15, 1.0/20); //size | step
    Graph graph(10, 10);
    graph.Plot(input);
}