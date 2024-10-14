/*
 utils.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: General utilities implementation for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/utilities/utils.hpp"
#include "atlas/opengl/glm/ext/vector_float3.hpp"
#include "atlas/unit.hpp"
#include <iostream>

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

void FunctionQueue::clear() {
    while (!general_queue.empty()) {
        general_queue.pop();
    }
}

void FunctionQueue::execute() {
    if (!general_queue.empty()) {
        general_queue.front()();
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

glm::vec3 Position::get() {
    return glm::vec3(x, y, z);
}

glm::vec3 Size::get() {
    return glm::vec3(width, height, depth);
}

Component::Component(std::string name, std::string type, Position position, Size size) : name(name), type(type), position(position), size(size) {
    ComponentRepresentation representation = ComponentRepresentation(name, type, position, size);
    ComponentTree::components.push_back(ComponentRepresentation(name, type, position, size));

}

}
