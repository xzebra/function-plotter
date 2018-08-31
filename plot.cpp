#include "plot.h"

// Plot prints just once the function
void Graph::Plot(std::string infix) {
    Operation *op = mathParser.toPostfix(infix);
    fillValues(op);
    plot();
    clearMemory();
}

// Loop constantly prints a function that changes over time. A function
// with at least variable name t is required.
void Graph::Loop(std::string infix) {
    Operation *op = mathParser.toPostfix(infix);
    double t = 0;
    for(;;) {
        fillValues(op, t);
        plot();
        t += 0.01;
        const int t100 = t * 100;
        sleep(100);
        std::cout << "t = " << t << (t100 % 10 == 0 ? " " : "") << " s " <<  std::endl;
        cls(3);
    }
    clearMemory();
}

Graph::Graph(int si, double st) {
    size = si;
    step = st;
    values = new int[size+size+1];
}

void Graph::cls(int offset) {
    for(int i = 0; i < size*2 + offset; i++) std::cout << "\x1b[A";
}

void Graph::clearMemory() {
    delete[] values;
}

// ----------------- PRIVATE -----------------
double Graph::round(double number) {
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

void Graph::sleep(int milliseconds) {
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end) {}
}

void Graph::fillValues(Operation *op) {
    for(int i = 0; i < size+size+1; ++i) {
        // Give each variable a value
        for(int j = 0; j < op->v_values.size(); j++) {
            op->v_values[j] = (i - (size)) * step;
        }
        // EQUATION
        std::string postfix_replaced = replaceVars(op);
        double value = mathParser.Solve(postfix_replaced);
        /// EQUATION
        value = value/step;
        values[i] = int(round(value));
    }
}

void Graph::fillValues(Operation *op, double t) {
    for(int i = 0; i < size+size+1; ++i) {
        // Give each variable a value
        for(int j = 0; j < op->v_values.size(); j++) {
            if(op->postfix[op->v_pos[j]] == 't') op->v_values[j] = t;
            else op->v_values[j] = (i - (size)) * step;
        }
        // EQUATION
        std::string postfix_replaced = replaceVars(op);
        double value = mathParser.Solve(postfix_replaced);
        /// EQUATION
        value = value/step;
        values[i] = int(round(value));
    }
}

void Graph::plot() {
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

std::string Graph::replaceVars(const Operation *op) {
    std::ostringstream output;
    int offset = 0;
    for(int p = 0; p < op->v_pos.size(); p++) {
        // Add rest of postfix expression from last replaced var
        for(int i = offset; i < op->v_pos[p]; i++) {
            output << op->postfix[i];
        }
        output << op->v_values[p];
        offset = op->v_pos[p]+1;
    }
    // Add the rest of the string if not added
    for(int p = offset; p < op->postfix.length(); p++) {
        output << op->postfix[p];
    }
    return output.str();
}