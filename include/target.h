#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <ctime>
#include "fileinfo.h"

/// Class responsible for representing a file in the directory tree
class Target {
    std::string m_name; ///< The name of the file
    bool m_exists; ///< Boolean standing for the file's existence
    time_t m_modtime; ///< The file's last modification time
public:

    /// Target constructor
    /// @param filename - the name of the file to represent
    Target(const std::string& filename)
        : m_name(filename)
        , m_exists(info::exists(filename))
        //, m_modtime(info::modtime(filename))
    {
        if(m_exists) {
            m_modtime = info::modtime(m_name);
        } else {
            m_modtime = std::time(0);
        }
    }

    /// Getter for the file's name
    /// @return a const reference to the filename
    const std::string& name() const {
        return m_name;
    }

    /// Function to check if the file exists
    /// @return boolean for the existence
    bool exists() const {
        return m_exists;
    }

    /// Getter for the modification time
    /// @return the last modification time
    time_t modtime() const {
        return m_modtime;
    }
};

#endif //TARGET_H
