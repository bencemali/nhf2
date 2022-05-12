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

    Rule& operator[](const std::string& name) const;

    const char* build(const std::string& target) const;
};

#endif //DATABASE_H
