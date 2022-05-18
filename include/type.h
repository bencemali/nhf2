#ifndef TYPE_H
#define TYPE_H
//#include "memtrace.h"
#include <vector>
#include <string>

/// Enum for a Makefile's lines' types
enum LineType {
    comment,
    recipe,
    rule,
    assignment,
    neutral
};

/// Function to determine a Makefile's lines' types
/// @param lines - the vector of the lines
/// @return a vector of the types
std::vector<LineType> type(std::vector<std::string*> lines);

#endif //TYPE_H
