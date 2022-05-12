#include "type.h"

bool is_comment(std::string* line) {
    if(line->size() == 0) {
        return false;
    }
    int pos = line->find_first_not_of(" \t\n\r\v");
    return (*line)[pos] == '#' ? true : false;
}

bool is_recipe(std::string* line) {
    if(line->size() == 0) {
        return false;
    }
    return (*line)[0] == '\t' ? true : false;
}

bool is_rule(std::string* line) {
    if(line->size() == 0) {
        return false;
    }
    size_t pos = line->find(':');
    if(pos == std::string::npos) {
        return false;
    } else if(pos != (line->size() - 1) && (*line)[pos + 1] == '=') {
        return false;
    }
    return true;
}

bool is_assignment(std::string* line) {
    if(line->size() == 0) {
        return false;
    }
    size_t pos = line->find('=');
    if(pos == std::string::npos) {
        return false;
    }
    return true;
}

std::vector<LineType> type(std::vector<std::string*> lines) {
    std::vector<LineType> vec(lines.size(), neutral);
    for(size_t i = 0; i < lines.size(); ++i) {
        if(is_comment(lines[i])) {
            vec[i] = comment;
        } else if(is_recipe(lines[i])) {
            vec[i] = recipe;
        } else if(is_rule(lines[i])) {
            vec[i] = rule;
        } else if(is_assignment(lines[i])) {
            vec[i] = assignment;
        } else {
            vec[i] = neutral;
        }
    }
    return vec;
}
