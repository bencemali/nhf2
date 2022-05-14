#include "fileinfo.h"

bool info::exists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

time_t info::modtime(const std::string& filename) {
    struct stat fileinfo;
    stat(filename.c_str(), &fileinfo);
    return fileinfo.st_mtime;
}
