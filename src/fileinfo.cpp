#include "fileinfo.h"

bool info::exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

time_t info::modtime(const std::string& name) {
    struct stat fileinfo;
    stat(name.c_str(), &fileinfo);
    return fileinfo.st_mtime;
}
