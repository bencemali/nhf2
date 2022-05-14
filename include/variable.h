#ifndef VARIABLE_H
#define VARIABLE_H
#include "memtrace.h"
#include <vector>
#include <string>
#include "type.h"

//temporary
#include <iostream>
//

class Variable {
    std::string m_name;
    std::string m_value;
public:
    Variable(const std::string& name, const std::string& value)
        : m_name(name)
        , m_value(value)
    {}

    const std::string& name() const {
        return m_name;
    }

    const std::string& value() const {
        return m_value;
    }

    void operator+=(const std::string& addition) {
        m_value += " ";
        m_value += addition;
    }
};

std::string strip(std::string&);

std::vector<Variable> extract_variables(std::vector<std::string*>, std::vector<LineType>);

#endif //VARIABLE_H
