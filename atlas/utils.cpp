/*
 utils.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: General utilities implementation for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/utilities/utils.hpp"

namespace atlas {

void FunctionQueue::push(std::function<void()> func) {
    general_queue.push(func);
}

void FunctionQueue::execute_all() {
    while (!general_queue.empty()) {
        general_queue.front()();
        general_queue.pop();
    }
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

}
