#ifndef RULE_H
#define RULE_H
#include <vector>
#include <string>
#include <stdexcept>
#include "target.h"
#include "recipe.h"
#include "type.h"
#include "variable.h"

class Rule {
    Target m_target;
    std::vector<std::string> m_dependencies;
    Recipe m_recipe;
public:
    Rule(const std::string& target, std::vector<std::string> deps, std::vector<std::string*> lines)
        : m_target(target)
        , m_dependencies(deps)
        , m_recipe(lines)
    {}

    const std::string& name() const {
        return m_target.name();
    }

    bool exists() const {
        return m_target.exists();
    }

    time_t modtime() const {
        return m_target.modtime();
    }

    void execute() const {
        m_recipe.execute();
    }
};

void substitute(std::string*, std::vector<Variable>&);

std::vector<Rule*> make_rules(std::vector<std::string*>& lines, std::vector<LineType>&, std::vector<Variable>&);

#endif //RULE_H
