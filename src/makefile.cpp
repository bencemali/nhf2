#include "makefile.h"
#include <fstream>

std::vector<std::string*> read_file(const std::string& filename) {
    std::ifstream file_stream(filename.c_str());
    if(!file_stream.is_open()) {
        throw std::runtime_error("Couldn't open target makefile named '" + filename + "'");
    }
    std::vector<std::string*> line_vector;
    std::string buffer;
    while(std::getline(file_stream, buffer)) {
        std::string* ptr = new std::string(buffer);
        line_vector.push_back(ptr);
    }
    return line_vector;
}
