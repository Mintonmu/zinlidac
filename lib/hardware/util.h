#ifndef LIBZINLIDAC_HARDWARE_UTIL_H
#define LIBZINLIDAC_HARDWARE_UTIL_H

#include "lib/error/error.h"

#include <string>
#ifdef __linux__
#include <unistd.h>
#endif

namespace libzinlidac {
    namespace hardware {
    class SysconfError : Error {
    private:
        std::string target;
    public:
        SysconfError(std::string &&target) {
            this->target = target;
        }

        std::string description() {
            return std::string("Cannot access ") + this->target;
        }
    };

    class SysinfoError : Error {
    public:
        std::string description() {
            return std::string("Cannot get sysinfo");
        }
    };

    class FileReadError : Error {
    private:
        std::string file_path;
    public:
        FileReadError(std::string &&file_path) {
            this->file_path = file_path;
        }

        std::string description() {
            return std::string("Cannot read file ") + this->file_path;
        }
    }

    #ifdef __linux__
    long int get_result_using_sysconf(int __name, std::string &&target) {
        long int result = sysconf(__name);
        if (result >= 0) {
            return result;
        } else {
            throw SysconfError(std::move(target));
        }
    }
    #endif
    }
}

#endif