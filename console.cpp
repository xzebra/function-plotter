#include <iostream>
#include <string>
#include "console.h"

void Console::parseCommand(std::string &s) {
    // parse function

}

void Console::loop() {
    std::string input;
    while(getline(std::cin, input)) {
        if(input == "quit()") break;
        parseCommand(input);
    }
}