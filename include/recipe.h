#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>

/// Class responsible for holding and executing commands
class Recipe {
    std::vector<std::string*> m_lines; ///< Vector of the lines
public:

    /// Recipe consructor
    /// @param lines - vector of line pointers deemed as commands
    Recipe(const std::vector<std::string*> lines)
        :m_lines(lines)
    {}

    /// Function to retrieve the lines held
    /// @return vector holding the lines
    std::vector<std::string*> lines() const {
        return m_lines;
    }

    /// Function to execute the held commands
    /*!
     * The paramaters are needed to substitute the potential automatic variables
     * (ie. $@, $<, $^)
     */
    /// @param target_name - the name of the Target of the Rule that the Recipe is part of
    /// @param dependencies - vector of the dependencies of the target
    void execute(const std::string& target_name, const std::vector<std::string>& dependencies) const;
};

/// Function to substitute automatic variables in a line
/// @param str_ptr - pointer to the string
/// @param target_name - name of the Target of the Rule the Recipe is part of
/// @param dependencies - vector of the dependencies of the target
std::string substitute(std::string* const str_ptr, const std::string& target_name, const std::vector<std::string>& dependencies);

#endif //RECIPE_H

