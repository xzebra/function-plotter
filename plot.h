#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <string>
#include <time.h>
#include <cmath>
#include <cstdarg>


template <class a_type> class Graph {
    public:
        void printGraph();
        void cls(int offset);
        void clearMemory();

        void fillValues(int n_args, a_type (*function)(a_type ...));
        //void fillValues(double (*function)(double x));
        //void fillValues(double (*function)(double x, double t), double t);

        void loop(double (*function)(double x));
        void loop(double (*function)(double x, double t));
        Graph(int si, double st);
        void plot();
    private:
        int size;
        double step;
        int *values;

        const std::string red = "\e[0;31m";
        const std::string green = "\033[0;32m";
        const std::string blue = "\e[0;34m";
        const std::string NC = "\033[0m";

        const std::string axis = "+ ";
        
        //char used to plot: green #
        const std::string line = green + "# " + NC;
        const std::string graph = "  ";

        a_type round(a_type number);

        void sleep(int milliseconds);
};

#endif