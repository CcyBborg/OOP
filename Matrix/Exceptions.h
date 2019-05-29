#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace containers::exceptions {
    class Exception : std::exception {
    public:
        Exception(std::string filename, std::string classname, int line, const char *time, std::string info) {
            errInfo = "filename: " + filename + "\nclass name: " + classname + "\nline: " + std::to_string(line)
                    + "\ntime: " + time + "\binfo: " + info;
        }

        virtual const char* what(void) const noexcept override
        {
            return this->errInfo;
        }

    protected:
        std::string errInfo;
    };

    class MatrixIndexOutOfBoundsException : public Exception {
    public:
        MatrixIndexOutOfBoundsException(std::string filename, std::string classname, int line, const char *time, std::string info) : Exception(filename, classname, line, time, info) {}
    };

    class MemoryAllocationException : public Exception {
    public:
        MemoryAllocationException(std::string filename, std::string classname, int line, const char *time, std::string info) : Exception(filename, classname, line, time, info) {}
    };

    class MatrixInvalidSizeException : public Exception {
    public:
        MatrixInvalidSizeException(std::string filename, std::string classname, int line, const char *time, std::string info) : Exception(filename, classname, line, time, info) {}
    };
}

#endif