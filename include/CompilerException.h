#pragma once
#include <stdexcept>
#include <string>

struct CompilerException : public std::runtime_error {
    CompilerException(const char* what_arg)
        : runtime_error(what_arg)
    {
    }

    CompilerException(const std::string& what_arg)
        : runtime_error(what_arg.c_str())
    {
    }
};
