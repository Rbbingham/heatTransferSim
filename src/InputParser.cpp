#include "InputParser.h"

#include <algorithm>
#include <stdexcept>

// constructor: throws each argument in vector of strings
InputParser::InputParser (int &argc, char **argv) {
    for (int i=1; i < argc; ++i) {
        this->tokens.emplace_back(std::string(argv[i]));
    }
}

// finds argument "option" and returns the values immediately after argument
const std::string& InputParser::getCmdOption (const std::string &option) const {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);

    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }

    // if not found return empty string
    throw std::invalid_argument(option);
}

// check of argument exists
bool InputParser::cmdOptionExists (const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}