#include "database.h"
#include <iostream>

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
    std::vector<std::string> dependencies = pattern_rule->deps();
    for(size_t i = 0; i < dependencies.size(); ++i) {
        if(dependencies[i].find("%") != std::string::npos) {
            size_t pos2 = dependencies[i].find("%");
            dependencies[i].replace(pos2, 1, name_without_pattern);
        }
    }
    Rule rule(name, dependencies, pattern_rule->lines());
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
    throw std::runtime_error("No rule for target '" + name + "'");
}

void Database::build_helper(const std::string& target_name, std::vector<std::string>& already_built) const {
    already_built.push_back(target_name); //Prevent loops by keeping a list of already built targets

    Rule target = (*this)[target_name];

    for(auto dep_name : target.deps()) {
        bool dep_already_built = false; //Prevent loops
        for(auto built : already_built) {
            if(built == dep_name) {
                dep_already_built = true;
            }
        }
        if(dep_name != target_name && !dep_already_built) {
            build_helper(dep_name, already_built);
        } else if(dep_name == target_name) {
            std::cout << "Target '" << target_name << "' is it's own prerequisite. Breaking loop." << '\n';
        } else if(dep_already_built) {
            std::cout << "Target '" << target_name << "' is in a loop. Breaking loop." << '\n';
        }
    }

    if(!target.exists()) {
        target.execute();
    } else {
        bool build_needed = false;
        for(auto dep_name : target.deps()) {
            if(target.modtime() < (*this)[dep_name].modtime()) {
                build_needed = true;
                break;
            }
        }
        if(build_needed) {
            target.execute();
        }
    }
}

void Database::build(const std::string& target_name) const {
    std::vector<std::string> already_built;
    already_built.push_back(target_name);

    build_helper(target_name, already_built);
}
