#include <iostream>
#include "plot.h"

int main(int argc, char *argv[]) {
    Parser mathParser = Parser();
    double size = 10;
    double step = 1;

    if(argc == 3) {
        size = std::stod(argv[1]);
        step = std::stod(argv[2]);
    }
    
    std::string input;
    std::cout << "y = ";
    std::getline(std::cin, input);
    
    Graph graph(size, step);
    //graph.Plot(input);
    graph.Loop(input);
}