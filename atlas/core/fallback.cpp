/*
 fallback.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Fallback for all errors
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/core/exec_error.hpp"
#include "atlas/utilities/style.hpp"
#include <iostream>

void (*atlas::RuntimeFallback::default_fallback)(std::string*) = nullptr;

void atlas::ExecutionError::express() {
    if (atlas::RuntimeFallback::default_fallback != nullptr) {
        atlas::RuntimeFallback::default_fallback(&message);
    } else {
        std::cout<< RED << BOLD << "AtlasEngine execution error at runtime:" << RESET << std::endl;
        std::cout << RED << message << RESET << std::endl;
    } 
}
