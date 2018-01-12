#include <iostream>
#include <cmath>
#include "plot.hpp"
using namespace std;

double function1(double x) {
    return x*x*x;
}

double function2(double x, double t) {
    return 0.1*cos(8*3.1416*t - 4*3.1416*x);
}

int main() {
    Graph graph(15, 1.0/20); //size | step

    //Example 1
    cout << "\e[0;32mSTATIC EXAMPLE:\e[0m" << endl;
    graph.fillValues(&function1);
    graph.printGraph();
    graph.clearMemory();

    cout << "\n\n" << "\e[0;32mANIMATED EXAMPLE:\e[0m" << endl;
    graph.loop(&function2);
    graph.clearMemory();
}
