#include "variable.h"

std::string strip(std::string& str) {
    std::string stripped;
    int begin = str.find_first_not_of(" \t\n\r\f\v");
    int end = str.find_last_not_of(" \t\n\r\f\v");
    return stripped = str.substr(begin, end - begin + 1);
}

std::vector<Variable> extract_variables(std::vector<std::string*> lines, std::vector<LineType> types) {
    std::vector<Variable> vec;
    for(size_t i = 0; i < types.size(); ++i) {

    }
}
