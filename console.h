
#include "plot.h"

class Console {
    public:
        Console() = default;
        ~Console() = default;
        void loop();
    private:
        void parseCommand(std::string &s);
        Graph graph;
};