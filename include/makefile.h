#ifndef MAKEFILE_H
#define MAKEFILE_H
#include <vector>
#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include "rule.h"
#include "variable.h"
#include "type.h"
#include "fileinfo.h"

/// Function to read a file's lines into a vector
/// @param filename - file to read from
/// @return vector of string pointers, the file's lines
std::vector<std::string*> read_file(const std::string& filename);

/// Class responsible for reading the desired Makefile
/*!
 * It reads the target Makefile's contents into strings,
 * determines the type of each line (ie. comment, assignment, ...),
 * creates the variables, and creates the rules.
 */
class Makefile {
    std::vector<std::string*> m_lines; ///< Vector of string pointers holding the lines
    std::vector<LineType> m_types; ///< Vector of line types, one for each line
    std::vector<Variable> m_variables; ///< Vector of variables created from assignments
    std::vector<Rule*> m_rules; ///< Vector of the created Rules (allocated and freed by Makefile)
public:

    /// Constructor for Makefile
    /// @param filename - file to interpret as the Makefile
    Makefile(const std::string& filename = "Makefile") {
        if(info::exists(filename)) {
            m_lines = read_file(filename);
            m_types = type(m_lines);
            m_variables = extract_variables(m_lines, m_types);
            for(auto line : m_lines) {
                substitute(line, m_variables);
            }
            m_rules = make_rules(m_lines, m_types, m_variables);
        } else {
            throw std::runtime_error("Target makefile named '" + filename + "' doesn't exist");
        }
    }

    /// Function for retrieving the Rules
    /// @return vector of dynamically allocated Rules
    std::vector<Rule*> rules() const {
        return m_rules;
    }

    /// Makefile destructor
    /// Frees the allocated lines and rules.
    virtual ~Makefile() {
        for(auto line : m_lines) {
            delete line;
        }
        for(auto rule : m_rules) {
            delete rule;
        }
    }
};

#endif //MAKEFILE_H

