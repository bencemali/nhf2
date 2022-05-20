#ifndef RULE_H
#define RULE_H
#include <vector>
#include <string>
#include <stdexcept>
#include "target.h"
#include "recipe.h"
#include "type.h"
#include "variable.h"

/// Class responsible for representing a rule to make a Target
class Rule {
    Target m_target; ///< The target entity
    std::vector<std::string> m_dependencies; ///< A list of the names of the dependencies
    Recipe m_recipe; ///< A recipe to 'make' the target
public:

    /// Rule constructor
    /// @param target - name of the target
    /// @param deps - list of the dependencies
    /// @param lines - the recipe's lines
    Rule(const std::string& target, std::vector<std::string> deps, std::vector<std::string*> lines)
        : m_target(target)
        , m_dependencies(deps)
        , m_recipe(lines)
    {}

    /// Rule constructor
    /// @param target - name of the target
    /// @param deps - list of the dependencies
    /// @param recipe - the Recipe
    Rule(const std::string& target, std::vector<std::string> deps, Recipe& recipe)
        : m_target(target)
        , m_dependencies(deps)
        , m_recipe(recipe)
    {}

    /// Getter for the target's namespace
    /// @return the target's name
    const std::string& name() const {
        return m_target.name();
    }

    /// Getter for the dependencies
    /// @return a vector of the dependencies' names
    const std::vector<std::string>& deps() const {
        return m_dependencies;
    }

    /// Getter for the recipe lines
    /// @return the Recipe's lines
    std::vector<std::string*> lines() const {
        return m_recipe.lines();
    }

    /// Function to check if the target exists in the directory tree
    /// @return bool for the existence
    bool exists() const {
        return m_target.exists();
    }

    /// Function to check the modification time of the target
    /// @return time_t for the last modification time
    time_t modtime() const {
        return m_target.modtime();
    }

    /// Function to execute the Recipe
    void execute() const {
        m_recipe.execute(m_target.name(), m_dependencies);
    }
};

/// Function to substitue variables in a line
/// @param line - pointer to the line
/// @param vars - a vector of the possible variables
void substitute(std::string* line, std::vector<Variable>& vars);

/// Function to get Rules from a Makefile's lines
/// @param lines - the Makefile's lines
/// @param types - the types of the lines (ie. comment, assignment, ...)
/// @param variables - a vector of the variables declared in the Makefile
/// @return a vector of the dynamically allocated Rules
std::vector<Rule*> make_rules(std::vector<std::string*>& lines, std::vector<LineType>& types, std::vector<Variable>& variables);

#endif //RULE_H

