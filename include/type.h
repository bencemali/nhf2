#ifndef TYPE_H
#define TYPE_H
#include "memtrace.h"
#include <vector>
#include <string>

enum LineType {
    comment,
    recipe,
    rule,
    assignment,
    neutral
};

/// Function to determine the lines' types
std::vector<LineType> type(std::vector<std::string*> lines);

#endif //TYPE_H
