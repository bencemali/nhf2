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

bool file_exists(const std::string& filename);

std::vector<std::string*> read_file(const std::string& filename);

/// Class responsible for reading the desired Makefile and creating the rules
class Makefile {
    std::vector<std::string*> m_lines;
    std::vector<LineType> m_types;
    std::vector<Variable> m_variables;
    std::vector<Rule*> m_rules; //TODO: Add to UML
public:
    Makefile(const std::string& filename = "Makefile") {
        if(file_exists(filename)) {
            m_lines = read_file(filename);
                        for(auto x : m_lines) {
                            std::cout << *x << '\n';
                        }
            m_types = type(m_lines);
                        for(auto x : m_types) {
                            switch(x) {
                                case comment:
                                    std::cout << "comment" << '\n';
                                    break;
                                case recipe:
                                    std::cout << "recipe" << '\n';
                                    break;
                                case rule:
                                    std::cout << "rule" << '\n';
                                    break;
                                case assignment:
                                    std::cout << "assignment" << '\n';
                                    break;
                                default:
                                    std::cout << "neutral" << '\n';
                            }
                        }
            m_variables = extract_variables(m_lines, m_types);
                        for(auto x : m_variables) {
                            std::cout << "VARIABLE: [" << x.name() << "] [" << x.value() << ']' << '\n';
                        }
            // m_rules = make_rules(m_lines, m_types, m_variables);
        } else {
            throw std::runtime_error("Target makefile named '" + filename + "' doesn't exist");
        }
    }

    std::vector<Rule*> rules() const;

    virtual ~Makefile() {
        for(auto x : m_lines) {
            delete x;
        }
        for(auto x : m_rules) {
            delete x;
        }
    }
};

#endif //MAKEFILE_H
