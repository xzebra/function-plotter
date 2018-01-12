#include <iostream>
#include <time.h>
using namespace std;

class Graph {
    public:
        void printGraph();
        void cls(int offset);
        void clearMemory();

        void fillValues(double (*function)(double x));
        void fillValues(double (*function)(double x, double t), double t);

        void loop(double (*function)(double x));
        void loop(double (*function)(double x, double t));
        Graph(int si, double st);
    private:
        int size;
        double step;
        int *values;

        const std::string red = "\e[0;31m";
        const std::string green = "\e[0;32m";
        const std::string blue = "\e[0;34m";
        const std::string NC = "\e[0m";

        const std::string axis = "+ ";
        //char used to plot: green #
        const std::string line = green + "# " + NC;
        const std::string graph = "  ";

        double round(double number) {
            return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
        }

        void sleep(int milliseconds) {
            clock_t time_end;
            time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
            while (clock() < time_end) {}
        }
};

void Graph::loop(double (*function)(double x, double t)) {

    double t = 0;
    while(1) {
        fillValues(function, t);
        printGraph();
        t += 0.01;
        const int t100 = t * 100;
        sleep(100);
        cout << "t = " << t << (t100 % 10 == 0 ? " " : "") << " s " <<  endl;
        cls(3);
    }
}

void Graph::fillValues(double (*function)(double x)) {
    for(int i = 0;i< size+size+1;++i) {
        double x = (i - (size));
        x = x*step;
        // EQUATION
        double value = (*function)(x);
        /// EQUATION
        value = value/step;
        values[i] = int(round(value));
    }
}

void Graph::fillValues(double (*function)(double x, double t), double t) {
    for(int i = 0;i< size+size+1;++i) {
        double x = (i - (size));
        x = x*step;
        // EQUATION
        double value = (*function)(x, t);
        /// EQUATION
        value = value/step;
        values[i] = int(round(value));
    }
}

Graph::Graph(int si, double st) {
    size = si;
    step = st;
    values = new int[size+size+1];
}

void Graph::cls(int offset) {
    for(int i = 0; i < size*2 + offset; i++) cout << "\x1b[A";
}

void Graph::plot() {
    cout << '\n';
    for(int i = 0;i < size;++i) {
        cout << ' ';
        for(int b = 0; b < size;++b) {
            if(size - i == values[b]) cout << line;
            else cout << graph;
        }

        if(size -i == values[size]) cout << line;
        else cout << axis;

        for(int b = 0; b < size;++b) {
            if(size - i == values[b+size+1]) cout << line;
            else cout << graph;
        }
        cout << endl;
    }

    cout << ' ';
    for(int i = 0;i < size*2+1;++i) {
        if( 0 == values[i] ) cout << line;
        else cout << axis;
    }
    cout << endl;

    for(int i = 0;i < size;++i) {
        cout << ' ';
        for(int b = 0; b < size;++b) {
            if(0-i-1 == values[b]) cout << line;
            else cout << graph;
        }
        if(0 -i-1 == values[size]) cout << line;
        else cout << axis;

        for(int b = 0; b < size;++b) {
            if(0-i-1 == values[b+size+1]) cout << line;
            else cout << graph;
        }
        cout << endl;
    }
}

void Graph::clearMemory() {
    delete[] values;
}
