#include "rule.h"
#include <iostream>
#include <cstring>
#include <algorithm>

void substitute(std::string* line, std::vector<Variable>& vars) {
    while(line->find("$(") != std::string::npos) {
        size_t sub_str_start = line->find("$(");
        if(line->size() >= sub_str_start + 2) {
        }
        size_t name_start = sub_str_start + 2;
        size_t sub_str_end = name_start + 1;
        do {
            if(line->c_str()[sub_str_end] == ')') {
                break;
            }
            ++sub_str_end;
        } while(sub_str_end < line->size());
        if((*line)[sub_str_end] != ')') {
            std::cout << "Missing ')' separator" << '\n';
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
                break;
            }
        }
        if(!var_found) {
            line->replace(sub_str_start, sub_str_end - sub_str_start + 1, "");
        }
    }
}

std::string ws_collapse(std::string str) {
    str = strip(str);
    std::string buffer = "";
    bool after_ws = false;
    for(auto it = str.begin(); it != str.end(); ++it) {
        if(isspace(*it)) {
            if(!after_ws) {
                buffer.push_back(*it);
            }
            after_ws = true;
        } else {
            buffer.push_back(*it);
            after_ws = false;
        }
    }
    return buffer;
}

std::vector<std::string> parse(const std::string& str) {
    std::vector<std::string> vec;
    if(str.size() > 0) {
        std::string temp = "";
        for(auto c : str) {
            if(!isspace(c)) {
                temp += c;
            } else {
                vec.push_back(temp);
                temp = "";
            }
        }
        vec.push_back(temp);
    }
    return vec;
}

std::vector<Rule*> make_rules(std::vector<std::string*>& lines, std::vector<LineType>& types, std::vector<Variable>& variables) {
    std::vector<Rule*> vec;
    for(size_t i = 0; i < types.size(); ++i) {
        if(types[i] == rule) {
            substitute(lines[i], variables);
            size_t separator_idx = lines[i]->find_first_of(":");

            //TARGETS
            std::string targets = lines[i]->substr(0, separator_idx);
            targets = ws_collapse(targets);

            //DEPENDENCIES
            std::string deps = lines[i]->substr(separator_idx + 1);
            deps = ws_collapse(deps);

            std::vector<std::string> target_names = parse(targets);
            std::vector<std::string> dep_names = parse(deps);

            std::vector<std::string*> recipe_lines;
            for(size_t j = i + 1; j != types.size() && types[j] == recipe; ++j) {
                recipe_lines.push_back(lines[j]);
            }

            for(auto target_name : target_names) {
                if(target_name != "") {
                    for(auto it = vec.begin(); it != vec.end();) {
                        if((*it)->name() == target_name) {
                            std::cout << "Overriding rule for '" << target_name << "'" << '\n';
                            delete *it;
                            vec.erase(it);
                        } else {
                            ++it;
                        }
                    }

                    bool pattern_dep = false;
                    for(auto dep_name : dep_names) {
                        if(dep_name.find("%") != std::string::npos) {
                            pattern_dep = true;
                            break;
                        }
                    }

                    Rule* ptr = nullptr;
                    if(pattern_dep && target_name.find("%") == std::string::npos) {
                        std::vector<std::string> filtered_dep_names = dep_names;
                        for(auto it = filtered_dep_names.begin(); it != filtered_dep_names.end() && filtered_dep_names.size() > 0;) {
                            if((*it).find("%") != std::string::npos) {
                                filtered_dep_names.erase(it);
                            } else {
                                ++it;
                            }
                        }
                        ptr = new Rule(target_name, filtered_dep_names, recipe_lines);
                    } else {
                        ptr = new Rule(target_name, dep_names, recipe_lines);
                    }
                    vec.push_back(ptr);
                }
            }
        }
    }
    return vec;
}
