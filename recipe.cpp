#include "recipe.h"
#include <iostream>

void Recipe::substitute(const std::string& target_name, const std::vector<std::string>& dependencies) const {
    //TODO: Substitute $@, $^, $< in Recipe
    //placeholder
    auto str = target_name;
    auto tmp = dependencies;
}

void Recipe::execute() const {
    for(auto line_ptr : m_lines) {
        std::cout << *line_ptr << '\n';
        //system(lineptr->c_str());
    }
}
