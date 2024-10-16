/*
 utils.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: General utilities for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_UTILS_HPP
#define ATLAS_UTILS_HPP

#include "atlas/component.hpp"
#include "atlas/opengl/glm/ext/matrix_float4x4.hpp"
#include "atlas/unit.hpp"
#include <functional>
#include <queue>
#include <string>
#include <vector>
namespace atlas {

class FunctionQueue {
public:
    std::queue<std::function<void()>> general_queue = std::queue<std::function<void()>>();
    void push(std::function<void()> func);
    void execute_all();
    void clear();
    void execute();

    
};

class ComponentTree {
public:
    static std::vector<ComponentRepresentation*> components;
};

std::string trim(const std::string& str);
std::vector<std::string> split(const std::string& str, const std::string& delimiter);
void printMatrix(const glm::mat4& matrix);
};

#endif // ATLAS_UTILS_HPP
