#ifndef VARIABLE_H
#define VARIABLE_H
//#include "memtrace.h"
#include <vector>
#include <string>
#include "type.h"

/// Class representing a declared variable
class Variable {
    std::string m_name; ///< The variable's name
    std::string m_value; ///< The variable's value
public:

    /// Variable constructor
    /// @param name - the variable's name
    /// @param value - the variable's value
    Variable(const std::string& name, const std::string& value)
        : m_name(name)
        , m_value(value)
    {}

    /// Getter for the variable's name
    /// @return const reference to the name
    const std::string& name() const {
        return m_name;
    }

    /// Getter for the variable's value
    /// @return const reference to the value
    const std::string& value() const {
        return m_value;
    }

    /// operator+= to append to the variable's value
    /// @param addition - the string to append to the value
    void operator+=(const std::string& addition) {
        m_value += " ";
        m_value += addition;
    }
};

/// Function to remove whitespaces from the beginning and end of a string
/// @param str - string to be stripped
/// @return the stripped string
std::string strip(std::string& str);

/// Function to extract variables from a Makefile's lines
/// @param lines - the vector of the Makefile's lines
/// @param types - the type of the Makefile's lines
/// @return a vector of the extracted variables
std::vector<Variable> extract_variables(std::vector<std::string*> lines, std::vector<LineType> types);

#endif //VARIABLE_H
