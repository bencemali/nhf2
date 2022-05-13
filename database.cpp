#include "database.h"

bool matches(const std::string& pattern_candidate, const std::string& name) {
    if(pattern_candidate.size() <= 1 || pattern_candidate[0] != '%') {
        return false;
    }
    std::string pattern = pattern_candidate.substr(1);
    if(name.find(pattern) == std::string::npos) {
        return false;
    }
    size_t pos = name.find(pattern);
    std::string pattern_match = name.substr(pos);
    if(pattern_match != pattern) {
        return false;
    }
    return true;
}

Rule temporary_rule(Rule* pattern_rule, const std::string& name) {
    size_t pos = name.find(pattern_rule->name()[1]);
    std::string name_without_pattern = name.substr(0, pos);
    std::vector<std::string> dependencies = pattern_rule->m_dependencies;
    for(auto dep : dependencies) {
        if(dep.find("%") != std::string::npos) {
            size_t pos2 = dep.find("%");
            dep.replace(pos2, 1, name_without_pattern);
        }
    }
    Rule rule(name, dependencies, pattern_rule->m_recipe.lines());
    return rule;
}

Rule Database::operator[](const std::string& name) const {
    for(auto rule_ptr : m_rules) {
        if(rule_ptr->name() == name) {
            return *rule_ptr;
        }
    }
    for(auto candidate : m_rules) {
        if(matches(candidate->name(), name)) {
            return temporary_rule(candidate, name);
        }
    }
    throw std::runtime_error("No rule for target " + name);
}

std::string Database::build(const std::string& target_name) const {
    Rule target = (*this)[target_name];
    for(auto dep : target.deps()) {
        (*this)[dep].execute();
    }
    //TODO: Finish Database
}
