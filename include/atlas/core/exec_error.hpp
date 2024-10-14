/*
 exec_error.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Execution error representable for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_EXEC_ERROR_HPP
#define ATLAS_EXEC_ERROR_HPP

#include <string>

namespace atlas {

class ExecutionError {
public:
    std::string message;
    bool default_fallback;
    ExecutionError(std::string message, bool default_fallback = false) : message(message), default_fallback(default_fallback) {};
    void express(); 
};

class RuntimeFallback {
public:
    static void (*default_fallback)(std::string*);
};

}

#endif // ATLAS_EXEC_ERROR_HPP
