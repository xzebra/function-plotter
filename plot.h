#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <string>
#include <time.h>
#include <cmath>
#include <cstdarg>

#include "mathParser/mathParser.h"

class Graph {
    public:
        void cls(int offset);
        void clearMemory();

        void Plot(std::string infix);
        void Loop(std::string infix);

        Graph(int si, double st);
    private:
        int size;
        double step;
        int *values;

    // windows does not allow ansi escape colors
    #if defined(_WIN32) || defined(__CYGWIN__)
        const std::string red = "";
        const std::string green = "";
        const std::string blue = "";
        const std::string NC = "";
    #else
        const std::string red = "\e[0;31m";
        const std::string green = "\033[0;32m";
        const std::string blue = "\e[0;34m";
        const std::string NC = "\033[0m";
    #endif // end colors

        const std::string axis = "+ ";
        
        //char used to plot: green #
        const std::string line = green + "# " + NC;
        const std::string graph = "  ";

        double round(double number);
        void sleep(int milliseconds);
        void plot();

        void fillValues(Operation *op);
        void fillValues(Operation *op, double t);
        std::string replaceVars(const Operation *op);

        Parser mathParser;
};

#endif