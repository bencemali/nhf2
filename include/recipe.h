#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>

/// Class responsible for holding and executing commands
class Recipe {
    std::vector<std::string*> m_lines;
public:
    Recipe(const std::vector<std::string*> lines)
        :m_lines(lines)
    {}

    std::vector<std::string*> lines() const {
        return m_lines;
    }

    void execute(const std::string&, const std::vector<std::string>&) const;
};

std::string substitute(std::string* const str_ptr, const std::string&, const std::vector<std::string>&);

#endif //RECIPE_H

