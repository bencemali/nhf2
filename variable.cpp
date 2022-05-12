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
        if(types[i] == assignment) {
            if(lines[i]->find("?=") != std::string::npos) {
                std::string name = lines[i]->substr(0, lines[i]->find("?="));
                name = strip(name);
                bool already_assigned = false;
                for(auto var : vec) {
                    if(var.name() == name) {
                        already_assigned = true;
                    }
                }
                if(!already_assigned) {
                    std::string value;
                    value = lines[i]->substr(lines[i]->find("=") + 1, lines[i]->size() - 1);
                    value = strip(value);
                    Variable neu_var(name, value);
                    vec.push_back(neu_var);
                }
            } else if(lines[i]->find("+=") != std::string::npos) {
                std::string name = lines[i]->substr(0, lines[i]->find("+="));
                name = strip(name);
                bool already_assigned = false;
                int idx = 0; idx += idx;
                for(size_t i = 0; i < vec.size(); ++i) {
                    if(vec[i].name() == name) {
                        already_assigned = true;
                        idx = i;
                    }
                }
                std::string value;
                value = lines[i]->substr(lines[i]->find("=") + 1, lines[i]->size() - 1);
                value = strip(value);
                if(!already_assigned) {
                    Variable neu_var(name, value);
                    vec.push_back(neu_var);
                } else {
                    vec[i] += value;
                }
            } else if(lines[i]->find("=") != std::string::npos) {
                std::string name = lines[i]->substr(0, lines[i]->find("="));
                name = strip(name);
                std::string value;
                value = lines[i]->substr(lines[i]->find("=") + 1, lines[i]->size() - 1);
                value = strip(value);
                Variable neu_var(name, value);
                vec.push_back(neu_var);
            }
        }
    }
    return vec;
}
