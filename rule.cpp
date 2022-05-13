#include "rule.h"
#include <cstring>

////////////
#include <iostream>
////////////

void substitute(std::string* line, std::vector<Variable>& vars) {
    while(line->find("$(") != std::string::npos) {
        size_t sub_str_start = line->find("$(");
        size_t name_start = sub_str_start + 2;
        size_t sub_str_end = name_start + 1;
        do {
            if(line->c_str()[sub_str_end] == ')') {
                break;
            }
            ++sub_str_end;
        } while(sub_str_end < line->size());
        if((*line)[sub_str_end] != ')') {
            throw std::runtime_error("Missing ')' separator");
        }
        std::string variable_name;
        for(size_t i = name_start; line->c_str()[i] != ')'; ++i) {
            variable_name.push_back(line->c_str()[i]);
        }
        bool var_found = false;
        for(auto var : vars) {
            if(var.name() == variable_name) {
                var_found = true;
                line->replace(sub_str_start, sub_str_end - sub_str_start + 1, var.value());
            }
        }
        if(!var_found) {
            line->replace(sub_str_start, sub_str_end - sub_str_start + 1, "");
        }
        break;
    }
}

std::vector<Rule*> make_rules(std::vector<std::string*> lines, std::vector<LineType>& types, std::vector<Variable>& variables) {
    std::vector<Rule*> vec;
    for(size_t i = 0; i < types.size(); ++i) {
        if(types[i] == rule) {
            substitute(lines[i], variables);
            //TODO: Create Rules from rule type line and add recipe lines without substitution
        }
    }
    return vec;
}
