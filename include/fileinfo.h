#include <sys/stat.h>
#include <string>
#include <stdexcept>

namespace info {

    /// Function to check if a file exists in the directory tree
    /// @param filename - name of the file to check
    /// @return boolean for the file's existance
    bool exists(const std::string& filename);


    /// Function to get the last modification time of a file
    /// @param filename - name of the file to check
    /// @return time_t of the last modification
    time_t modtime(const std::string& filename);
}
