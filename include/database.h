#ifndef DATABASE_H
#define DATABASE_H
//#include "memtrace.h"
#include <vector>
#include "rule.h"

/// Class responsible for building the desired target
class Database {
    std::vector<Rule*> m_rules; ///< Vector holding all the rules

    /// Helper function for Database::build()
    /*!
     * The function is needed to keep track of the previously built
     * targets, and eliminate loops.
     */
    /// @param target_name - name of the target
    /// @param already_built - vector of the target names, that the function was called upon
    void build_helper(const std::string& target_name, std::vector<std::string>& already_built) const;
public:

    /// Constructor
    /// @param rules - vector of rules from Makefile class
    Database(std::vector<Rule*> rules)
        : m_rules(rules)
    {}

    /// Operator[] to search for a Rule by it's target's name
    /*!
     * With this function you can search for a 
     * rule by the target's name. It returns by value
     * since it needs to realize pattern rules (ie. %.o: %.c)
     */
    /// @param name - name of the sought Rule's target's name
    /// @return the sought rule by value
    Rule operator[](const std::string&) const;

    /// Interface function to build a target
    /*!
     * This function will create a list (vector) of targets
     * already built and passes it on to Database::build_helper().
     * It is needed to avoid getting into a loop.
     */
    /// @param target_name - name of the top level build target
    void build(const std::string& target_name) const;
};

/// Function to test if a target name matches a pattern (ie. %)
/// @param pattern_candidate - pattern to test against
/// @param name - name to test
bool matches(const std::string& pattern_candidate, const std::string& name);

/// Function to create a temporary rule from patterns
/// @param pattern_rule - pattern rule to be based on
/// @param name - name of the actual target
Rule temporary_rule(Rule* pattern_rule, const std::string& name);

#endif //DATABASE_H

