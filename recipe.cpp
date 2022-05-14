#include "recipe.h"
#include <iostream>

std::string substitute(std::string* const str_ptr, const std::string& target_name, const std::vector<std::string>& dependencies) {
    std::string ret = *str_ptr;
    while(ret.find("$@") != std::string::npos) {
        size_t pos = ret.find("$@");
        ret.replace(pos, 2, target_name);
    }
    while(ret.find("$<") != std::string::npos) {
        size_t pos = ret.find("$<");
        ret.replace(pos, 2, dependencies[0]);
    }
    while(ret.find("$^") != std::string::npos) {
        std::string all_deps = "";
        for(size_t i = 0; i < dependencies.size(); ++i) {
            if(i != 0) {
                all_deps += " ";
            }
            all_deps += dependencies[i];
        }
        size_t pos = ret.find("$^");
        ret.replace(pos, 2, all_deps);
    }
    return ret;
}

void Recipe::execute(const std::string& target_name, const std::vector<std::string>& dependencies) const {
    for(auto line_ptr : m_lines) {
        std::string subst_line = substitute(line_ptr, target_name, dependencies);
        std::cout << "OUTPUT: "<< subst_line << '\n';
        //system(subst_line.c_str());
    }
}
