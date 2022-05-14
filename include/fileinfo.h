#include <sys/stat.h>
#include <string>
#include <stdexcept>

namespace info {
    bool exists(const std::string& filename);
    time_t modtime(const std::string& name);
}
