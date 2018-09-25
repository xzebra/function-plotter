#include <iostream>
#include "plot.h"

bool checkError(int argc, int i) {
    if(i+1 >= argc) {
        std::cout << "Args error" << std::endl;
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    double size = 10;
    double step = 1;
    bool loop = false;

    for(int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "-size") {
            if(checkError(argc, i)) return 1;
            size = std::stod(argv[++i]);
        } else if(arg == "-step") {
            if(checkError(argc, i)) return 1;
            step = std::stod(argv[++i]);
        } else if(arg == "-l" || arg == "-loop") {
            loop = true;
        }
    }
    
    std::string input;
    std::cout << "y = ";
    std::getline(std::cin, input);
    
    Graph graph(size, step);
    if(!loop) graph.Plot(input);
    else graph.Loop(input);

    return 0;
}