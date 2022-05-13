#ifndef MAKEFILE_H
#define MAKEFILE_H

/////////////////////
#include <iostream>
/////////////////////

#include <vector>
#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include "rule.h"
#include "variable.h"
#include "type.h"
#include "fileinfo.h"

std::vector<std::string*> read_file(const std::string& filename);

/// Class responsible for reading the desired Makefile and creating the rules
class Makefile {
    std::vector<std::string*> m_lines;
    std::vector<LineType> m_types;
    std::vector<Variable> m_variables;
    std::vector<Rule*> m_rules; //TODO: Add to UML
public:
    Makefile(const std::string& filename = "Makefile") {
        if(info::exists(filename)) {
            m_lines = read_file(filename);
            m_types = type(m_lines);
            m_variables = extract_variables(m_lines, m_types);
                        for(auto variable : m_variables) {
                            std::cout << "VARIABLE: [" << variable.name() << "] [" << variable.value() << ']' << '\n';
                        }
            m_rules = make_rules(m_lines, m_types, m_variables);
            for(auto line : m_lines) {
                substitute(line, m_variables);
                std::cout << ">> " << *line << '\n';
            }
        } else {
            throw std::runtime_error("Target makefile named '" + filename + "' doesn't exist");
        }
    }

    std::vector<Rule*> rules() const;

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
