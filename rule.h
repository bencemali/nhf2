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

    Rule(const std::string& target, std::vector<std::string> deps, Recipe& recipe)
        : m_target(target)
        , m_dependencies(deps)
        , m_recipe(recipe)
    {}

    const std::string& name() const {
        return m_target.name();
    }

    const std::vector<std::string>& deps() const {
        return m_dependencies;
    }

    bool exists() const {
        return m_target.exists();
    }

    time_t modtime() const {
        return m_target.modtime();
    }

    void execute() const {
        m_recipe.execute(m_target.name(), m_dependencies);
    }

    friend Rule temporary_rule(Rule*, const std::string&);
};

void substitute(std::string*, std::vector<Variable>&);

std::vector<Rule*> make_rules(std::vector<std::string*>& lines, std::vector<LineType>&, std::vector<Variable>&);

#endif //RULE_H

