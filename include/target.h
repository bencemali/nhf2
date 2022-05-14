#ifndef TARGET_H
#define TARGET_H
#include <string>
#include <ctime>
#include "fileinfo.h"

class Target {
    std::string m_name;
    bool m_exists;
    time_t m_modtime;
public:
    Target(const std::string& filename)
        : m_name(filename)
        , m_exists(info::exists(filename))
        , m_modtime(info::modtime(filename))
    {}

    const std::string& name() const {
        return m_name;
    }

    bool exists() const {
        return m_exists;
    }

    time_t modtime() const {
        return m_modtime;
    }
};

#endif //TARGET_H
