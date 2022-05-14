#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "rule.h"

/// Class responsible for building the targets
class Database {
    std::vector<Rule*> m_rules;
public:
    Database(std::vector<Rule*> rules)
        : m_rules(rules)
    {}

    Rule operator[](const std::string&) const;

    void build(const std::string&) const; //TODO: Change in UML to std::string
};

bool matches(const std::string&, const std::string&);

Rule temporary_rule(Rule*, const std::string&);

#endif //DATABASE_H

