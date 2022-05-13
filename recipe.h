#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>

/// Class responsible for holding and executing commands
class Recipe {
    std::vector<std::string*> m_lines;
public:
    Recipe(const std::vector<std::string*> lines) {
        m_lines = lines;
    }

    void substitute(const std::string& target_name, std::vector<std::string>& dependencies);

    void execute() const;
};

#endif //RECIPE_H
