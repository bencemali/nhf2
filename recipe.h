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

    void operator+=(std::string* line) {
        m_lines.push_back(line);
    }

    void execute() const;
};

#endif //RECIPE_H
