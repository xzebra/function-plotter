#include "plot.h"

template <class a_type>
void Graph<a_type>::loop(double (*function)(double x, double t)) {
    double t = 0;
    while(1) {
        fillValues(function, t);
        plot();
        t += 0.01;
        const int t100 = t * 100;
        sleep(100);
        std::cout << "t = " << t << (t100 % 10 == 0 ? " " : "") << " s " <<  std::endl;
        cls(3);
    }
}

template <class a_type>
void Graph<a_type>::fillValues(int n_args, a_type (*function)(a_type ...)) {
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

/*void Graph::fillValues(double (*function)(double x)) {
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

        double value = (*function)(x, t);

        value = value/step;
        values[i] = int(round(value));
    }
}*/

template <class a_type>
Graph<a_type>::Graph(int si, double st) {
    size = si;
    step = st;
    values = new int[size+size+1];
}

template <class a_type>
void Graph<a_type>::cls(int offset) {
    for(int i = 0; i < size*2 + offset; i++) std::cout << "\x1b[A";
}

template <class a_type>
void Graph<a_type>::plot() {
    std::cout << '\n';
    for(int i = 0; i < size; ++i) {
        std::cout << ' ';
        for(int b = 0; b < size;++b) {
            if(size - i == values[b]) std::cout << line;
            else std::cout << graph;
        }

        if(size -i == values[size]) std::cout << line;
        else std::cout << axis;

        for(int b = 0; b < size;++b) {
            if(size - i == values[b+size+1]) std::cout << line;
            else std::cout << graph;
        }
        std::cout << std::endl;
    }

    std::cout << ' ';
    for(int i = 0; i < size*2+1;++i) {
        if(!values[i]) std::cout << line;
        else std::cout << axis;
    }
    std::cout << std::endl;

    for(int i = 0; i < size;++i) {
        std::cout << ' ';
        for(int b = 0; b < size;++b) {
            if(0-i-1 == values[b]) std::cout << line;
            else std::cout << graph;
        }
        if(0 -i-1 == values[size]) std::cout << line;
        else std::cout << axis;

        for(int b = 0; b < size;++b) {
            if(0-i-1 == values[b+size+1]) std::cout << line;
            else std::cout << graph;
        }
        std::cout << std::endl;
    }
}

template <class a_type>
void Graph<a_type>::clearMemory() {
    delete[] values;
}

// PRIVATE:
template <class a_type>
a_type Graph<a_type>::round(a_type number) {
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
template <class a_type>
void Graph<a_type>::sleep(int milliseconds) {
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end) {}
}